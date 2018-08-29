#include "in_rturecv.h"

IN_RtuRecv::IN_RtuRecv()
{

}



bool IN_RtuRecv::rtuRecvCrc(uchar *buf, int len, IN_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "IN_RtuRecv rtu recv crc Err!";
    }

    return ret;
}


/**
  * 功　能：长度 校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：0 正确
  */
int IN_RtuRecv::rtuRecvLen(uchar *buf, int len)
{
    int ret = 0;
    int rtn = IN_RTU_SENT_LEN+5;
    if(len < rtn) rtn = IN_RTU_SENT_DC_LEN+5;

    if(len < rtn) {  //判断是否为交流数据
        ret = -1;
        //  qDebug() << "rtu recv Err: len too short!!" << len  << rtn;
    } else if(len > rtn) {
        ret = -2;
        qDebug() << "IN si rtu recv Err: len too long!!" << len << rtn ;
    } else {
        //  len = buf[2]*256 + buf[3];
        len = buf[2] + 5;
        if(len != rtn) {
            ret = -3;
            qDebug() << "in rtu recv len Err!!"<< len << rtn  ;
        }
    }

    return ret;
}

/**
  * 功　能：读取数据包头部
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：0 正确
  */
int IN_RtuRecv::rtuRecvHead(uchar *ptr,  IN_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > IN_ARRAY_LEN) pkt->len = 0;

    return 3;
}

/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
int IN_RtuRecv::rtuRecvData(uchar *ptr, IN_sRtuLine *msg)
{
    msg->vol =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电压
    msg->cur =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电流
    msg->pow =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取功率
    msg->ele =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
    msg->ele <<= 8; // 左移8位
    msg->ele +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位

    msg->maxVol =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    msg->minVol =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    msg->maxCur =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    msg->minCur =  (*ptr) * 256 + *(ptr+1);  ptr += 2;

    msg->wave =  (*ptr) * 256 + *(ptr+1);  ptr += 2;    // 谐波值
    msg->pf =  *(ptr++);// 功率因素
    msg->sw =  *(ptr++);// 开关状态

    msg->apPow = msg->vol * msg->cur / 10.0; // 视在功率

    return 22;   //功率因素之后，是为22
}


/**
  * 功　能：读取环境 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
int IN_RtuRecv::rtuRecvEnv(uchar *ptr, IN_sRtuEnvUnit *msg)
{
    msg->value = *(ptr++);
    msg->max = *(ptr++);
    msg->min = *(ptr++);

    return 3;
}


/**
 * @brief 二分二路直流 数据交换
 * @param pkt
 */
void IN_RtuRecv::rtuRecvSwap(IN_sRtuRecv *pkt)
{
    if((2 == pkt->rate) && (2 == pkt->lineNum)) //交换2-3数据
    {
        IN_sRtuLine data;
        data = pkt->data[1];
        pkt->data[1] = pkt->data[2];
        pkt->data[2] = data;
    }
}

/**
  * 功　能：还原数据包
  * 入口参数：buf -> 缓冲区   len -> 数据长度
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
bool IN_RtuRecv::recvPacket(uchar *buf, int len, IN_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 5) && (len < IN_ARRAY_LEN)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            int rtn = rtuRecvLen(buf, len); //判断回收的数据是否完全
            if(rtn == 0) {
                uchar *ptr=buf;
                ptr += rtuRecvHead(ptr, pkt); //指针偏移

                pkt->dc = *(ptr++);  //[交直流]
                pkt->rate = *(ptr++);
                for(int i=0; i<IN_RTU_TH_NUM; ++i) // 读取环境 数据
                    ptr += rtuRecvEnv(ptr, &(pkt->env[i].tem));
                pkt->lineNum = *(ptr++); //[输出位]
                pkt->version = *(ptr++); //[输出位]
                ptr += 2;

                int lineNum = 0;
                if(pkt->dc) lineNum = IN_RTU_LINE_NUM;
                else lineNum = IN_RTU_DCLINE_NUM;

                for(int i=0; i<lineNum; ++i) // 读取电参数
                    ptr += rtuRecvData(ptr, &(pkt->data[i]));

                if(pkt->dc == 0)  rtuRecvSwap(pkt);
            }
        }
    }

    return ret;
}
