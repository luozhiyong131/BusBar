#include "serialtrans.h"

SerialTrans::SerialTrans(QObject *parent) : QThread(parent)
{
    mutex = new QMutex();
    mSerial = new SerialPort();
}

SerialTrans:: ~SerialTrans()
{
    wait();
    mSerial->close();
}

bool SerialTrans::openSerial(const QString &name)
{
    return mSerial->open(name);
}


/**
  * 功　能：发送数据
  * 入口参数：pBuff -> 缓冲区   nCount -> 长度
  * 返回值：发送的实际长度  <=0 出错
  */
int SerialTrans::sendData(uchar *pBuff, int nCount, int msec)
{
    QMutexLocker locker(mutex);
    int ret = mSerial->send(pBuff, nCount);
    if(ret>=0) msleep(msec);

    return ret;
}


/**
  * 功　能：读取数据
  * 入口参数：pBuf -> 缓冲区
  * 返回值：读取的实际长度  <=0 出错
  */
int SerialTrans::recvData(uchar *pBuf, int msecs)
{
    QMutexLocker locker(mutex);
    int count=0, ret=0;
    do
    {
        int rtn = mSerial->recv(pBuf);
        if(rtn > 0) {
            pBuf += rtn; // 指针移动
            ret += rtn; // 长度增加
            count = msecs-1;
        } else {
            count++;
        }
    } while (count < msecs) ;
    return ret;
}


/**
  * 功　能：传输数据
  * 入口参数：sent -> 发送缓冲区, len ->  发送长度
  * 出口参数：recv -> 接收缓冲区
  * 返回值：读取的实际长度  <=0 出错
  */
int SerialTrans::transmit(uchar *sent, int len, uchar *recv, int msecs)
{
    int ret = sendData(sent, len, 100);
    if(ret > 0) {
        ret = recvData(recv, msecs);
        //         if(ret <=0 ) qDebug() << "Serial Trans Err!!!" << ret;
    }
    return ret;
}
