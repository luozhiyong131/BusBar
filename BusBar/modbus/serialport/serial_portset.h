#ifndef SERIAL_PORTSET_H
#define SERIAL_PORTSET_H

/**
  * 设置串口
  */
#include <QtCore>

#if defined(ARM_LINUX)
#define SERIAL_COM1     "ttyS8"
#else
#define SERIAL_COM1     "ttyUSB0"
#endif

#define SERIAL_BAUDRATE    "B9600"


struct Serial_PortData
{
    QString devName;
    QString baudRate;
    QString dataBit;
    QString parity;
    QString stopBit;
};


class Serial_PortSet
{
public:
    Serial_PortSet();

    void setPortName(const QString &, Serial_PortData &); // 设置端口名
    void setBaudRate(const QString, Serial_PortData &); // 设置波特率

private:
     Serial_PortData m_serialData;
};

#endif // SERIAL_PORTSET_H