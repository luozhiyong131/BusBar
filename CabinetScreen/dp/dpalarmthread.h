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
    void alarmDataUnit(sDataUnit &unit, bool cr=false);
    char alarmFlag(sDataUnit &unit, bool cr=false);

    void devAlarm(sDevData &dev);
    void packetAlarm(sDataPacket *packet);

protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPALARMTHREAD_H
