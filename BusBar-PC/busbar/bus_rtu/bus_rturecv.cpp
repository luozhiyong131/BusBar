/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_rturecv.h"


/**
  * 功　能：长度 校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：0 正确
  */
static int rtu_recv_len(uchar *buf, int len)
{
    int ret = 0;
    int rtn = BUS_RTU_SENT_LEN+5;
    if(len < rtn) rtn = BUS_RTU_SENT_DC_LEN+5;

    if(len < rtn) {  //判断是否为交流数据
        ret = -1;
        //  qDebug() << "rtu recv Err: len too short!!" << len  << rtn;
    } else if(len > rtn) {
        ret = -2;
        qDebug() << "bus si rtu recv Err: len too long!!" << len << rtn ;
    } else {
        //  len = buf[2]*256 + buf[3];
        len = buf[2] + 5;
        if(len != rtn) {
            ret = -3;
            qDebug() << "rtu recv len Err!!"<< len << rtn  ;
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
static int rtu_recv_head(uchar *ptr,  BUS_RtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/

    pkt->len = (*ptr) ; /*数据长度*/
    return 3;
}


/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
static int rtu_recv_data(uchar *ptr, BUS_RtuRecvLine *msg)
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

    msg->activePow = msg->vol * msg->cur / 10.0; // 视在功率

    return 22;   //功率因素之后，是为22
}


/**
  * 功　能：读取环境 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
static int rtu_recv_env(uchar *ptr, BUS_RtuEnvUnit *msg)
{
    msg->value = *(ptr++);
    msg->max = *(ptr++);
    msg->min = *(ptr++);

    return 3;
}

/**
  * 功　能：检验码 数据
  * 入口参数：buf -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
static bool rtu_recv_crc(uchar *buf, int len, BUS_RtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2;

    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "rtu recv crc Err!";
    }

    return ret;
}

/**
 * @brief 二分二路直流 数据交换
 * @param pkt
 */
static void rtu_recv_swap(BUS_RtuRecv *pkt)
{
    if((2 == pkt->rate) && (2 == pkt->lineNum)) //交换2-3数据
    {
        BUS_RtuRecvLine data;
        data = pkt->data[1];
        pkt->data[1] = pkt->data[2];
        pkt->data[2] = data;
    }
}

static int rtu_recv_thd(uchar *ptr, BUS_RtuRecv *msg)
{
    msg->lps = *(ptr++); // 防雷开关
     // 读取负载百分比
    for(int i=0; i<LINE_NUM; ++i) msg->pl[i] = *(ptr++);
    msg->hc = *(ptr++);

    int len = BUS_RTU_THD_NUM;
    if(msg->addr) len = LINE_NUM;
    for(int i=0; i<len; ++i){
        msg->thd[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return (1+3+1+len*2);
}


/**
  * 功　能：还原数据包
  * 入口参数：buf -> 缓冲区   len -> 数据长度
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
bool bus_rtu_recv_packet(uchar *buf, int len, BUS_RtuRecv *pkt)
{
    bool ret = false;

    int rtn = rtu_recv_len(buf, len); //判断回收的数据是否完全
    if(rtn == 0) {
        uchar *ptr=buf;
        ptr += rtu_recv_head(ptr, pkt); //指针偏移

        pkt->dc = *(ptr++);  //[交直流]
        pkt->rate = *(ptr++);
        for(int i=0; i<BUS_RTU_TH_NUM; ++i) // 读取环境 数据
            ptr += rtu_recv_env(ptr, &(pkt->env[i].tem));
        pkt->lineNum = *(ptr++); //[输出位]
        pkt->version = *(ptr++); //[输出位]
        ptr += 2;

        int lineNum = 0;
        if(pkt->dc) lineNum = pkt->lineNum;
        else lineNum = BUS_RTU_DCLINE_NUM;

        for(int i=0; i<lineNum; ++i) // 读取电参数
            ptr += rtu_recv_data(ptr, &(pkt->data[i]));

        if(pkt->dc) ptr += rtu_recv_thd(ptr, pkt);
        else rtu_recv_swap(pkt);

        pkt->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
        ret = rtu_recv_crc(buf, len, pkt); //校验码
    }
    return ret;
}

