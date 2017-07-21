#ifndef SERIAL_PORTSET_H
#define SERIAL_PORTSET_H

/**
  * 设置串口
  */
#include <QtCore>

#define ARM_LINUX 1

#if defined(ARM_LINUX)
#define SERIAL_COM1     "ttyS8"
#define SERIAL_COM2     "ttyS2"
#define SERIAL_COM3     "ttyS7"
#define SERIAL_COM4     "ttyS4"
#else
#define SERIAL_COM1     "ttyUSB0"
#define SERIAL_COM2     "ttyUSB1"
#define SERIAL_COM3     "ttyUSB2"
#define SERIAL_COM4     "ttyUSB3"
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
