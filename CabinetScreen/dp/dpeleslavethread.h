#ifndef DPELESLAVETHREAD_H
#define DPELESLAVETHREAD_H

#include <QObject>
#include "common.h"

class DpEleSlaveThread : public QThread
{
    Q_OBJECT
public:
    explicit DpEleSlaveThread(QObject *parent = 0);
    ~DpEleSlaveThread();

signals:

protected:
    void run();
    void saveCab();
    void saveDev(int id, sDevData &dev);

protected slots:
    void timeoutDone();

private:
    bool isRun;
    QTimer *timer;
    sDataPacket *shm;
};

#endif // DPELESLAVETHREAD_H
