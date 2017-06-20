#ifndef DPTHREAD_H
#define DPTHREAD_H

#include <QThread>
#include "common.h"

class DpThread : public QThread
{
    Q_OBJECT
public:
    explicit DpThread(QObject *parent = 0);
    ~DpThread();

signals:

protected:
    void run();



protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPTHREAD_H
