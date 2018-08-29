#ifndef SERIALTRANS_H
#define SERIALTRANS_H

#include "serialport.h"

class SerialTrans : public QThread
{
    Q_OBJECT
public:
    explicit SerialTrans(QObject *parent = nullptr);
    ~SerialTrans();

    bool openSerial(const QString &name);
    int sendData(uchar *pBuff, int nCount, int msec=100);

    int recvData(uchar *pBuf, int msecs);
    int transmit(uchar *sent, int len, uchar *recv, int msecs=5);

signals:

public slots:

private:
    SerialPort *mSerial;
    QMutex *mutex; // 互拆锁
};

#endif // SERIALTRANS_H
