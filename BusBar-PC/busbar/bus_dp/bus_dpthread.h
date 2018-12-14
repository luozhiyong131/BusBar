#ifndef DPTHREAD_H
#define DPTHREAD_H

#include "bus_dptgthread.h"

class BUS_DpThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpThread(QObject *parent = 0);
    ~BUS_DpThread();

signals:

protected slots:
    void initFunSLot();

private:
     BUS_DpTgThread *mTgThread;
     BUS_DpAlarmThread *mAlarmThread;
     BUS_DpEleSlaveThread *mEle;
     BUS_DpAlarmSlave *mAlarmSlave;
};

#endif // DPTHREAD_H
