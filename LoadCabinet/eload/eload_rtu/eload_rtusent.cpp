/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_rtusent.h"

ELoad_RtuSent::ELoad_RtuSent()
{
    mSerial = SerialTrans::bulid();
    mSentBuf = (uchar *)malloc(256);
}


ELoad_RtuSent *ELoad_RtuSent::bulid()
{
    static ELoad_RtuSent* sington = nullptr;
    if(sington == nullptr) {
        sington = new ELoad_RtuSent();
    }
    return sington;
}

int ELoad_RtuSent::setDataBuf(uchar addr, uchar fn, ushort reg, ushort value)
{
    uchar *buf = mSentBuf;
    sRtuSentCom cmd;
    cmd.addr = addr;
    cmd.fn = fn;
    cmd.reg = reg;
    cmd.len = value;
    int rtn = rtu_sent_packet(&cmd, buf);

    return mSerial->sendData(buf, rtn);
}

/**
 * @brief 设置数据参数
 * @param addr  从机地址  从机地址可设置范围：1~15
 * @param reg 数字电位器地址  1 ~ 8
 * @param value   参数（数字电位器阻值）可设置范围：40Ω~50KΩ
 * @param buf 数据缓冲区
 * @return 数据长度
 */
int ELoad_RtuSent::setData(uchar addr, ushort reg, ushort value)
{
    return setDataBuf(addr, ELoad_FN_Set, reg, value);
}

/**
 * @brief 波特率设置
 * @param addr
 * @param reg
 * @param value
 * @param buf
 * @return
 */
int ELoad_RtuSent::setBaudRate(uchar addr, ushort reg, ushort value)
{
    return setDataBuf(addr, ELoad_BR_Reg, reg, value);
}

int ELoad_RtuSent::switchOpenCtr(uchar addr,  uchar bit)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
    uchar sw = 0x80;
    sw >>= bit;
    cmd[3+addr] = sw;

    int offset = 14;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    return mSerial->sendData(buf, offset);
}


int ELoad_RtuSent::switchOpenAll(uchar addr)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
    cmd[3+addr] = 0xFF;

    int offset = 14;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    return mSerial->sendData(buf, offset);
}


int ELoad_RtuSent::switchCloseCtr(uchar addr,  uchar bit)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
    uchar sw = 0x80;
    sw >>= bit;
    cmd[9+addr] = sw;

    int offset = 14;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    return mSerial->sendData(buf, offset);
}

int ELoad_RtuSent::switchCloseAll(uchar addr)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
     cmd[9+addr] = 0xFF;

    int offset = 14;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

   return mSerial->sendData(buf, offset);
}

int ELoad_RtuSent::setDpAdjust(uchar addr, ushort reg, ushort start, ushort end, ushort t)
{
    int offset = 0;
    uchar *buf = mSentBuf;

    buf[offset++] = addr;
    buf[offset++] = ELoad_FN_Ctr;

    buf[offset++] = (reg >> 8);
    buf[offset++] = (reg & 0xff);

    buf[offset++] =  (start >> 8);
    buf[offset++] = (start & 0xff);

    buf[offset++] =  (end >> 8);
    buf[offset++] = (end & 0xff);

    buf[offset++] =  (t >> 8);
    buf[offset++] = (t & 0xff);

    ushort crc =rtu_crc(buf, offset);
    buf[offset++] = (crc >> 8);
    buf[offset++] = (crc & 0xff);

    return mSerial->sendData(buf, offset);
}

int ELoad_RtuSent::setAllDpAdjust(uchar addr, ushort start, ushort end, ushort t)
{
    int offset = 0;
    uchar *buf = mSentBuf;

    buf[offset++] = addr;
    buf[offset++] = ELoad_FN_AllCtr;

    buf[offset++] =  (start >> 8);
    buf[offset++] = (start & 0xff);

    buf[offset++] =  (end >> 8);
    buf[offset++] = (end & 0xff);

    buf[offset++] =  (t >> 8);
    buf[offset++] = (t & 0xff);

    ushort crc =rtu_crc(buf, offset);
    buf[offset++] = (crc >> 8);
    buf[offset++] = (crc & 0xff);

    return mSerial->sendData(buf, offset);
}

int ELoad_RtuSent::setBigCur(uchar addr, uchar sw)
{
    uchar cmd[16] = {0x7B, 0xA6, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD};
    cmd[2] = addr;
    cmd[4] = sw;

    int offset = 14;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

   return mSerial->sendData(buf, offset);
}

int ELoad_RtuSent::getHandshake(uchar addr)
{
    uchar cmd[10] = {0x7B, 0xB1, 0x01, 0x08, 0x11, 0x22};
    cmd[2] = addr;

    int offset = 8;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    return mSerial->transmit(cmd,offset, mSentBuf);
}
