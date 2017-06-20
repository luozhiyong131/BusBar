#include "dpthread.h"

DpThread::DpThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_share_mem(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

DpThread::~DpThread()
{
    isRun = false;
    wait();
}

void DpThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}










void DpThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        isRun  = false;
    }
}
