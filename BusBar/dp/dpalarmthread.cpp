#include "dpalarmthread.h"

DpAlarmThread::DpAlarmThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_share_mem(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

DpAlarmThread::~DpAlarmThread()
{
    isRun = false;
    wait();
}

void DpAlarmThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}



void DpAlarmThread::alarmDataUnit(sDataUnit &unit, bool cr)
{
    for(int i=0; i<3; ++i)
    {
        if((unit.value[i] < unit.min[i]) || (unit.value[i] > unit.max[i]))
        {
            if(unit.alarm[i] == 0)
                unit.alarm[i] = 1;
        } else
            unit.alarm[i] = 0;

        if(cr) {
            if((unit.value[i] < unit.crMin[i]) || (unit.value[i] > unit.crMax[i]))
            {
                if(unit.crAlarm[i] == 0)
                    unit.crAlarm[i] = 1;
            } else
                unit.crAlarm[i] = 0;
        }
    }
}





void DpAlarmThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

//        for(int i=0; i<BUS_NUM; ++i)
//            tgBus(&(shm->data[i]));

        isRun  = false;
    }
}
