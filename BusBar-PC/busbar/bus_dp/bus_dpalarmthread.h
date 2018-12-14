#ifndef DPALARMTHREAD_H
#define DPALARMTHREAD_H

#include "bus_dpalarmslave.h"

class BUS_DpAlarmThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpAlarmThread(QObject *parent = 0);
    ~BUS_DpAlarmThread();

signals:

protected:
    void run();
    int alarmDataUnit(sDataUnit &unit, bool cr=false);

    void boxAlarm(sDataPacket &box);
    void busAlarm(sDevPackets *bus);

protected slots:
    void timeoutDone();
    void initFunSLot();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPALARMTHREAD_H
