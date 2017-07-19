#ifndef RTUTHREAD_H
#define RTUTHREAD_H

#include <QThread>
#include "common.h"
#include "serialport/serial_trans.h"
#include "rtu485/rtu_recv.h"

#define RTU_BUF_SIZE 512

class RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit RtuThread(QObject *parent = 0);
    ~RtuThread();

    bool init(const QString& name, int id);
    
signals:    
    
protected:
    void run();
    void transData(int addr);

    void loopObjData(sObjData *loop, int id, RtuRecvLine *data);
    void loopData(sBoxData *box, Rtu_recv *pkt);

    void envData(sEnvData *env, Rtu_recv *pkt);

private:
    uchar *mBuf;
    Serial_Trans *mSerial;
    Rtu_recv *mRtuPkt;
    sBusData *mBusData;
    bool isRun;
};

#endif // RTUTHREAD_H
