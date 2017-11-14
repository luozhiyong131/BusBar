/*
 * dpalarmthread.cpp
 * 报警标志位判定线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "dpalarmthread.h"

DpAlarmThread::DpAlarmThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_dev_dataPacket(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(2*1000);
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
    for(int i=0; i<LINE_NUM; ++i)
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


char DpAlarmThread::alarmFlag(sDataUnit &unit, bool cr)
{
    char flag=0;

    for(int i=0; i<LINE_NUM; ++i) {
        flag += unit.alarm[i];
        if(flag) return 2;
    }

    for(int i=0; i<LINE_NUM; ++i) {
        if(cr) flag += unit.crAlarm[i];
        if(flag) return 1;
    }

    return flag;
}

void DpAlarmThread::devAlarm(sDevData &dev)
{
    alarmDataUnit(dev.data.cur); // 回路是否有报警
    dev.volAlarm = alarmFlag(dev.data.cur);

    alarmDataUnit(dev.data.vol); // 回路是否有报警
    dev.curAlarm = alarmFlag(dev.data.vol);

    alarmDataUnit(dev.env.tem);
    dev.temAlarm = alarmFlag(dev.env.tem);

    alarmDataUnit(dev.env.hum);
    dev.humAlarm = alarmFlag(dev.env.hum);

    dev.alarm = dev.volAlarm + dev.curAlarm + dev.temAlarm + dev.humAlarm;
}

void DpAlarmThread::packetAlarm(sDataPacket *packet)
{
    for(int i=0; i<DEV_NUM; ++i) {
        devAlarm(packet->dev[i]);
    }
}


void DpAlarmThread::run()
{
    if(isRun == false)
    {
        isRun  = true;
        packetAlarm(shm);
        isRun  = false;
    }
}
