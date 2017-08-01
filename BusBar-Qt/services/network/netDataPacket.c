/*
 * netDataPacket.c
 * 网络数据包
 * 	接口：int data_msg_packetSent(data_code *code,uchar *buf, ushort len)
 * 	说明：数据打包成协议格式，并发送出去
 *
 *	接口：int data_msg_analytic(uchar *buf, ushort len, data_packet *msg)
 *	说明：数据包解析，还原成data_packet结构体
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "netDataPacket.h"
#include "android_tcp_server.h"

static uchar gSentBuf[UDP_BUF_SIZE]={0};


/**
 * 功  能：生成校验码
 * 入口参数：pkt->包结构休
 * 返回值：校验码
 */
uchar data_packet_xor(uchar *buf, ushort len)
{
    ushort i;
    uchar XOR=0;

    for(i=0; i<len; ++i)
        XOR += buf[i];

    return XOR;
}


/**
 * 功  能：数据加入包头、结束符
 * 入口参数：pkt->包结构休
 * 返回值：
 */
static void data_packet_head(data_packet *pkt)
{
    pkt->hdr = DATA_MSG_HDR;	/*信息头*/
    pkt->stx = DATA_MSG_STX; /*标识字*/

    pkt->ED = DATA_MSG_ED; /*结束符*/
}

/**
 * 功能：填入代号段数据
 * 入口参数：msg->包结构休
 * 出口参数：buf->数据包首地址
 * 返回值：数据包长度
 */
static int data_packet_code(data_code *msg, uchar *buf)
{
    ushort i,rtn=DATA_MSG_CODE_SIZE; /*代码段字节数为9*/
    uchar *ptr = buf;

    /*填入代号段*/
    for(i=0; i<DEV_CODE_SIZE; ++i)
        *(ptr++) = msg->devCode[i];	/*设备号*/

    *(ptr++) = msg->type;	/*通讯类型*/
    *(ptr++) = msg->version; /*版本号*/
    *(ptr++) = msg->trans; /*传输方向*/

    msg->reserve = 0;
    memcpy(ptr, &(msg->reserve),sizeof(ushort)); /*预留号*/

    return rtn;
}

/**
 * 功能：填入数据域
 * 入口参数：msg->包结构休
 * 出口参数：buf->数据包首地址
 * 返回值：数据包长度
 */
static int data_packet_domain(data_packet *msg, uchar *buf)
{
    ushort i,rtn=0;
    uchar *ptr = buf;

    /*填入数据长度*/
    *(ptr++) = ((msg->len) >> 8); /*长度高8位*/
    *(ptr++) = (0xff)&(msg->len); /*低8位*/

    for(i=0; i<msg->len; ++i)
        *(ptr++) = msg->data[i];

    msg->XOR = data_packet_xor(msg->data, msg->len);	/*生成校验码*/
    *(ptr++) = msg->XOR;

    rtn = 2+ msg->len + 1;
    return rtn;
}

/**
 * 功能：数据打包
 * 入口参数：pkt->包结构休
 * 出口参数：buf->数据包首地址
 * 返回值：数据包长度
 * 说明：当要发送数据时就会调用此函数把数据打包
 */
static int data_msg_packet(data_packet *pkt, uchar *buf)
{
	ushort rtn=0;
	uchar *ptr = buf;

	data_packet_head(pkt); /*填写包头、包尾*/
	*(ptr++) = pkt->hdr;  /*信息头*/
	*(ptr++) = pkt->stx; /*标识字*/

	ptr += data_packet_code(&(pkt->code),ptr); /*填入代号段数据*/
	ptr += data_packet_domain(pkt, ptr); /*填入数据*/

	*(ptr++) = pkt->ED; /*结束符*/
	rtn = 2 + DATA_MSG_CODE_SIZE + 2 + pkt->len + 1 + 1;

    return rtn;
}

/**
 * 功能：数据发送
 * 入口参数：data_code -> 代号段构休 	buf->数据首地址 len ->数据长度
 * 返回值：数据包长度
 * 说明：当要发送数据时就会调用此函数发送数据
 */
int data_msg_packetSent(data_code *code,uchar *buf, ushort len)
{
	static data_packet msg;

	msg.code = *code;
	msg.len = len;
	msg.data = buf;

	memset(gSentBuf,0,sizeof(gSentBuf));
	len = data_msg_packet(&msg, gSentBuf); // 数据打包
	android_sent(gSentBuf,len);
	len = udp_clientSentData(gSentBuf,len);

	return len;
}


/**
 * 功  能：同步数据包 查检数据包是否完整
 * 入口参数：pkt->包结构休
 * 返回值：同步头的位置，   -2 同步头出错 	-3结束符错误
 */
static int data_packet_sync(uchar *buf, ushort len)
{
    int ret=0,rtn = -1;
    uchar head[2] = {DATA_MSG_HDR, DATA_MSG_STX}; /*包头*/
    ushort offset=0;

    if(len < 2+DATA_MSG_CODE_SIZE+3) /*数据包不完整*/
        return DATA_ERR_ABNORMAL;

    /*查找同步头*/
    do
    {
        if(offset < len-2)
        {
            ret = memcmp(buf+offset, head, sizeof(head)); /*查找包头*/
            if(ret!=0) /*不是包头*/
                offset++; /*偏量增加*/
        }
        else
            return DATA_ERR_HEAD; /*同步头错误*/
    } while(ret!=0);

    /*验证包尾*/
    rtn = offset + 2 + DATA_MSG_CODE_SIZE; /*代号段结束位置*/
    rtn += (buf[rtn]<<8) + buf[rtn+1]; /*数据长度*/
    rtn += 2+1; /*数据长度二字节、校验位一字节*/
    if(rtn < len)
    {
        if(buf[rtn] == DATA_MSG_ED) /**/
            return offset; /*返回头位置*/
    }

    return DATA_ERR_END;/*结束符未找到*/
}

/**
 * 功能：解析代号段数据
 * 入口参数：buf->数据首地址
 * 出口参数：code->打包之后MSG
 * 返回:长度
 */
static int data_packet_getCode(uchar *buf, data_code *code)
{
    uchar i,*ptr=buf;

    for(i=0; i<DEV_CODE_SIZE; ++i)
        code->devCode[i] = *(ptr++); /*设备代号*/

    code->type = *(ptr++); /*通讯类型*/
    code->version = *(ptr++); /*版本号*/
    code->trans = *(ptr++); /*服务端发送标志：10H 客户端应答标志：03H */
    code->reserve = 0; //(*(ptr++)) * 256;
    code->reserve += 0;//*(ptr++);

    return DATA_MSG_CODE_SIZE;
}

/**
 * 功  能：解析数据段数据
 * 入口参数：buf->数据首地址
 * 出口参数：msg->打包之后MSG
 * 返  回:长度 	-1 出错
 */
static int data_packet_getDomain(uchar *buf, data_packet *msg)
{
    ushort len=0;
    uchar XOR,*ptr = buf;

    len = (ptr[0]<<8) + ptr[1]; /*获取数据长度*/
    msg->len = len;
    ptr += 2;

    if(len > 0)
    {
        msg->data = ptr; /* 数据段*/
        ptr += len;
    }

    msg->XOR = *(ptr++);
    XOR = data_packet_xor(msg->data, len);
    if(XOR != msg->XOR)
        return DATA_ERR_XOR;

    return (2+len+1);
}


/**
 * 功能：解析数据包
 * 入口参数：buf->数据首地址 	len->数据长度
 * 出口参数：pkt->打包之后MSG
 * 返回:TRUE
 * 说明：当收到数据包时就会调用此函数把数据解包成MSG格式
 */
int data_msg_analytic(uchar *buf, ushort len, data_packet *msg)
{
    int ret;
    uchar *ptr=buf;

    ret = data_packet_sync(buf,len);
    if(ret >= 0)
    {
        ptr = buf+ret;
        msg->hdr = *(ptr++); /*信息头*/
        msg->stx = *(ptr++); /*标识字*/

        ptr += data_packet_getCode(ptr, &(msg->code)); /*获取代号段数据*/
        ret = data_packet_getDomain(ptr, msg);	/*获取数据段*/
        if(ret >= 0)
        {
            ptr += ret;
            msg->ED = *ptr;

            return (2+DATA_MSG_CODE_SIZE+2+msg->len+2); /*整个包的长度*/
        }
    }
    else
    	udp_printf("data packet sync error %d\n",ret);

    return ret;
}

