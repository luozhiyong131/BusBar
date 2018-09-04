#include "eload_rtusent.h"

ELoad_RtuSent::ELoad_RtuSent()
{

}

int ELoad_RtuSent::setDataBuf(uchar addr, uchar fn, ushort reg, ushort value, uchar *buf)
{
    sRtuSentCom cmd;
    cmd.addr = addr;
    cmd.fn = fn;
    cmd.reg = reg;
    cmd.len = value;

    return rtu_sent_packet(&cmd, buf);
}


/**
 * @brief 设置数据参数
 * @param addr  从机地址  从机地址可设置范围：1~15
 * @param reg 数字电位器地址  1 ~ 8
 * @param value   参数（数字电位器阻值）可设置范围：40Ω~50KΩ
 * @param buf 数据缓冲区
 * @return 数据长度
 */
int ELoad_RtuSent::setData(uchar addr, ushort reg, ushort value, uchar *buf)
{
    return setDataBuf(addr, ELoad_FN_Set, reg, value, buf);
}

/**
 * @brief 波特率设置
 * @param addr
 * @param reg
 * @param value
 * @param buf
 * @return
 */
int ELoad_RtuSent::setBaudRate(uchar addr, ushort reg, uchar value, uchar *buf)
{
    return setDataBuf(addr, ELoad_BR_Reg, reg, value, buf);
}

/**
 * @brief 开关控制
 * @param addr
 * @param reg
 * @param value
 * @param buf
 * @return
 */
int ELoad_RtuSent::switchCtr(uchar addr, ushort reg, uchar value, uchar *buf)
{
    return setDataBuf(addr, ELoad_FN_SW, reg, value, buf);
}


int ELoad_RtuSent::setDpAdjust(uchar addr, ushort reg, ushort start, ushort end, ushort t, uchar *buf)
{
    int offset = 0;

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

    return offset;
}

int ELoad_RtuSent::setAllDpAdjust(uchar addr, ushort start, ushort end, ushort t, uchar *buf)
{
    int offset = 0;

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

    return offset;
}
