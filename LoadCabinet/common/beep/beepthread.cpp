#include "beepthread.h"

BeepThread::BeepThread(QObject *parent) : QThread(parent)
{
    isRun = false ;

    system("echo 129 > /sys/class/gpio/export");
    system("echo \"out\" > /sys/class/gpio/gpio129/direction");
}

BeepThread *BeepThread::bulid()
{
    static BeepThread* sington = NULL;
    if(sington == NULL)
        sington = new BeepThread();
    return sington;
}

void BeepThread::beep()
{
    mSec = 100;
    start();
}

void BeepThread::longBeep()
{
    mSec = 650;
    start();
}

void BeepThread::run()
{

    if(isRun == false)
    {
        isRun  = true;
        system("echo \"1\" > /sys/class/gpio/gpio129/value");
        msleep(mSec);
        system("echo \"0\" > /sys/class/gpio/gpio129/value");
        msleep(400);
        isRun  = false;
    }
}
