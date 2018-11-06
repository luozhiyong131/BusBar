/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "serialport.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <QObject>
#include <qsocketnotifier.h>
#include <sys/termios.h>
#include <QDebug>
#include <QMutexLocker>

SerialPort::SerialPort()
{
    fd = -1;
}

SerialPort:: ~SerialPort()
{
    close();
}

/**
  * 功　能：打开端口
  * 入口参数：serialName> 设备名
  * 出口参数：
  * 返回值：true
  */
bool SerialPort::open(const QString &name)
{
    struct termios setting;
    fd = ::open(qPrintable("/dev/" + name), O_RDWR);
    if (fd == -1) { //串口是否存在
        //QMessageBox::warning(this, "open error", strerror(errno));
        qDebug() << "Serial Err::open "<< name;
        return false;
    }
    tcgetattr(fd, &setting);

    //  设置波特率
    speed_t speed = B9600;
    cfsetispeed(&setting, speed);
    cfsetospeed(&setting, speed);
    cfmakeraw(&setting);

    //  设置数据位
    setting .c_cflag |= CS8;

    //  设置parity
    setting.c_cflag &= ~PARENB;
    setting.c_iflag &= ~INPCK;

    //  设置停止位
    setting.c_cflag &= ~CSTOPB;

    tcflush(fd, TCIFLUSH);
    setting.c_cc[VTIME] = 2; // 超时时间 0.5S
    setting.c_cc[VMIN] = 0; // 数据最小长度
    tcsetattr(fd, TCSANOW, &setting);

    return true;
}

/**
  * 功　能：关闭端口
  * 入口参数：
  * 出口参数：
  * 返回值：
  */
void SerialPort :: close()
{
    if(fd >= 0)
    {
        ::close(fd);
        fd = -1;
    }
}


int SerialPort::send(uchar *pBuff, int nCount)
{
    if(fd >= 0)
    {
        int sendLen = write(fd, pBuff, nCount);
        fsync(fd);
        return sendLen;
    }

    return fd;
}

int SerialPort::recv(uchar *pBuf, int len)
{
    int ret = -1;

    if(fd>=0)
        ret = read(fd, pBuf, len);

    return ret;
}
