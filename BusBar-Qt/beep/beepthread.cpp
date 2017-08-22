#include "beepthread.h"
#include "gpio_dev.h"

BeepThread::BeepThread(QObject *parent) : QThread(parent)
{
    isRun = false ;
    gpio_init();
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

        msleep(50);
        gpio_on(2);
        msleep(mSec);
        gpio_off(2);
        msleep(300);

        isRun  = false;
    }
}
