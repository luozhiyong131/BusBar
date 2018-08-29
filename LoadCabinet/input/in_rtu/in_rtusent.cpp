/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_rtusent.h"

IN_RtuSent::IN_RtuSent()
{
    mMutex = new QMutex;
}


/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int IN_RtuSent::sentDataBuff(uchar addr,  uchar *buf)
{
    static IN_sRtuSent msg;
    QMutexLocker locker(mMutex);

    msg.addr = addr;
    return rtu_sent_packet(&msg, buf);
}

int IN_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static IN_sRtuSent msg;
    QMutexLocker locker(mMutex);

    msg.addr = addr;
    msg.fn   = 0x10;
    msg.reg  = reg;
    msg.len  = value;
    return rtu_sent_packet(&msg, buf);
}
