#ifndef RTUSENTCOM_H
#define RTUSENTCOM_H
#include <QtCore>

struct sRtuSentCom {
    sRtuSentCom():fn(3),reg(0),len(0){} // 下位机有问题
    uchar addr; // 表示从机地址码
    uchar fn;  // 表示功能码
    ushort reg; // 表示寄存器首地址
    ushort len; // 表示数据长度
    ushort crc; // 表示CRC校验
};

struct sRtuSetCmd
{
    int addr;
    int reg;
    ushort value;
};


int rtu_sent_packet(sRtuSentCom *pkt, uchar *ptr);
int zrtu_sent_packet(sRtuSentCom *pkt, uchar *ptr);
ushort rtu_crc(uchar *buf, int len);
uchar rtu_xorsum(uchar *buf, int len);
#endif // RTUSENTCOM_H
