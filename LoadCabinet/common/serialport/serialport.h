#ifndef SERIALPORT_H
#define SERIALPORT_H

/**
  * 设置串口
  */
#include <QtCore>

#define ARM_LINUX 1

#if ARM_LINUX == 1
#define SERIAL_COM1     "ttymxc2"
#define SERIAL_COM2     "ttymxc3"
#define SERIAL_COM3     "ttymxc4"
#define SERIAL_COM4     "ttymxc6"
#define SERIAL_COM5     "ttymxc1"
#else
#define SERIAL_COM1     "ttyUSB0"
#define SERIAL_COM2     "ttyUSB1"
#define SERIAL_COM3     "ttyUSB2"
#define SERIAL_COM4     "ttyUSB3"
#endif

#define SERIAL_BAUDRATE    "B9600"

class SerialPort
{
public:
    SerialPort();
    ~SerialPort();

    bool open(const QString &name);
    int recv(uchar *pBuf, int len=255);
    int send(uchar *pBuff, int nCount);
    void close();

private:
    int fd; //串口句柄
};

#endif // SERIALPORT_H
