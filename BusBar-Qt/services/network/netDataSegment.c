/*
 * datasegment.c
 * 数据段打包，解包
 *
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "netDataSegment.h"

static uchar gSentBuf[UDP_BUF_SIZE]={0};


/**
 *
 */
void data_dev_code(data_code *code)
{
	int i=0;
	for(i=0; i<DEV_CODE_SIZE; ++i)
		code->devCode[i] = 1; /*设备代号*/

	code->type = TRA_TYPR_UDP; /*通讯类型*/
	code->version = DATA_DEV_VERSION; /*版本号*/
	code->trans = DATA_MSG_CLIENT; /*服务端发送标志：10H 客户端应答标志：03H */
	code->reserve = 0;
}

/**
 * 功能：设备数据打包
 * 入口参数：pkt->包结构休
 * 出口参数：buf->数据包首地址
 * 返回值：数据包长度
 * 说明：当要发送数据时就会调用此函数把数据打包
 */
static int msg_packet(dev_data_packet *pkt, uchar *buf)
{
    ushort i,rtn=0;
    uchar *ptr = buf;

    *(ptr++) = pkt->addr; 	/*设备号*/

    *(ptr++) = pkt->fn[0]; /*功能码*/
    *(ptr++) = pkt->fn[1];

    /*数据长度*/
    *(ptr++) = (pkt->len >> 8); /*高八位*/
    *(ptr++) = (pkt->len) & 0xFF; /*低八位*/

    for(i=0; i<pkt->len; ++i)
    	 *(ptr++) = pkt->data[i];
    rtn = 1 + 2 + 2 + pkt->len;

    return rtn; /*数据包长度*/
}


/**
 *  发送数据函数
 */
int data_packet_sent(dev_data_packet *msg)
{
	ushort rtn=0;
	static data_code devCode; /*代号段*/
	data_dev_code(&devCode);

	memset(gSentBuf,0,sizeof(gSentBuf));
	rtn = msg_packet(msg,gSentBuf);
	rtn = data_msg_packetSent(&devCode, gSentBuf, rtn);

	return rtn;
}


/**
 * @brief  检查代码段
 * @param code
 * @return
 */
static int dev_code_check(data_code *code)
{
	int i;
    for(i=0; i<DEV_CODE_SIZE; ++i)
    {
        if(code->devCode[i] != 1) /*设备代号*/
            return false;
    }

    if((code->type != TRA_TYPR_UDP) && (code->type != TRA_TYPR_TCP))/*通讯类型*/
        return false;

    if(code->version != DATA_DEV_VERSION) /*版本号检查*/
        return false;

    if(code->trans != DATA_MSG_SERVICE) /*传输方向*/
        return false;

    return true;
}


/**
 * 功能：解析数据包
 * 入口参数：buf->数据首地址 	len->数据长度
 * 出口参数：pkt->打包之后MSG
 * 返回:TRUE
 */
static int msg_analytic(uchar *buf, ushort len, dev_data_packet *pkt)
{
    uchar *ptr=buf;

    pkt->addr = *(ptr++);/*获取源地址码*/

    pkt->fn[0] = *(ptr++); /*功能码*/
    pkt->fn[1] = *(ptr++);

    pkt->len = (*ptr) * 256 + *(ptr+1); /*数据长度*/
    ptr += 2;

    if(pkt->len > 0) /*数据区*/
        pkt->data = ptr;

    return pkt->len;
}


/**
 * 功能：解析数据包
 * 入口参数：buf->数据首地址 	len->数据长度
 * 出口参数：pkt->打包之后MSG
 * 返回:TRUE
 * 说明：当收到数据包时就会调用此函数把数据解包成MSG格式
 */
int data_packet_analytic(uchar *buf, ushort len, dev_data_packet *pkt)
{
    static data_packet msg;
    int ret = data_msg_analytic(buf,len,&msg);
    if(ret > 0)
    {
        ret = dev_code_check(&msg.code); /*代号段判断*/
        if(ret == true)
             ret = msg_analytic(msg.data, msg.len, pkt);
        else
        	udp_printf("dev code error\n");
        return ret;
    }
    else
    	udp_printf("dev data analytic error\n");

    return false;
}
