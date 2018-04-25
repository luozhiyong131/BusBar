#ifndef THIRDTHREAD_H
#define THIRDTHREAD_H

#include <QThread>
#include "serialport/serial_trans.h"
#include "rtu485/rtu_recv.h"
#include "common.h"

#define RTU_BUF_SIZE 100

struct ThrData {
    uchar addr; // 表示从机地址码 addr%64 - 那条母线_0起  addr%4 - 那条接插相_0起 [0 - 255]
    uchar fn; // 表示功能码
    ushort position; //地址地址位

    ushort len; // 表示数据字节数

    ushort crc; // 检验码
};

class ThirdThread : public QThread
{
    Q_OBJECT
public:
    explicit ThirdThread(QObject *parent = 0);

     bool init(const QString& name);

signals:

public slots:

protected:
    void run();
    void transData();

private:
    Serial_Trans *mSerial;
    bool isRun;
    uchar *mBuf;
    ThrData *mThr;
};

#endif // THIRDTHREAD_H
