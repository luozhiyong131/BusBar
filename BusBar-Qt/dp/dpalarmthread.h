#ifndef DPALARMTHREAD_H
#define DPALARMTHREAD_H

#include "dptgthread.h"

class DpAlarmThread : public QThread
{
    Q_OBJECT
public:
    explicit DpAlarmThread(QObject *parent = 0);
    ~DpAlarmThread();

signals:

protected:
    void run();
    void alarmDataUnit(sDataUnit &unit, int lineNum, bool cr=true);
    char alarmFlag(sDataUnit &unit, bool cr=true);

    void boxAlarm(sBoxData &box);
    void busAlarm(sBusData &bus);

protected slots:
    void timeoutDone();
    void initFunSLot();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPALARMTHREAD_H
