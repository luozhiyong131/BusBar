#ifndef DPTHREAD_H
#define DPTHREAD_H

#include <QThread>
#include "common.h"
#include "dpalarmthread.h"
#include "dpeleslavethread.h"
#include "dpalarmslave.h"

class DpThread : public QThread
{
    Q_OBJECT
public:
    explicit DpThread(QObject *parent = 0);
    ~DpThread();

signals:


private:
     DpTgThread *mTgThread;
     DpAlarmThread *mAlarmThread;
     DpEleSlaveThread *mEle;
     DpAlarmSlave *mAlarmSlave;
};

#endif // DPTHREAD_H
