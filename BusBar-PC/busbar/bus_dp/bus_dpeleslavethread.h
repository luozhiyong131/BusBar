#ifndef DPELESLAVETHREAD_H
#define DPELESLAVETHREAD_H

#include "bus_dpalarmthread.h"

class BUS_DpEleSlaveThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpEleSlaveThread(QObject *parent = 0);
    ~BUS_DpEleSlaveThread();

signals:

protected:
    void run();
    void saveBus(int id);
    void saveBox(int bus, sDataPacket &box);

protected slots:
    void timeoutDone();

private:
    bool isRun;
    QTimer *timer;
    sDataPacket *shm;
};

#endif // DPELESLAVETHREAD_H
