#include "setthread.h"

SetThread::SetThread(QObject *parent) : QThread(parent)
{
    isRun = true;
    mSetShm = new BUS_SetShm(this);
    mRtuCmd = new SetRtuCmd(this);
}

SetThread::~SetThread()
{
    isRun = false;
    wait();
}

SetThread *SetThread::bulid(QObject *parent)
{
    static SetThread* sington = NULL;
    if(sington == NULL) {
        sington = new SetThread(parent);
    }
    return sington;
}


void SetThread::workDown()
{
    if(mItems.size()) {
        sThresholdItem item = mItems.first();
        mRtuCmd->send(item);

        mSetShm->setItem(item);
        mItems.removeFirst();
        sleep(1);
    }
}

void SetThread::run()
{
    while (isRun) {
        workDown();
        msleep(1);
    }
}
