/*
 * dpalarmthread.cpp
 * 告警标志位判定线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "bus_dpalarmthread.h"

BUS_DpAlarmThread::BUS_DpAlarmThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    QTimer::singleShot(15*1000,this,SLOT(initFunSLot())); //延时初始化
}

BUS_DpAlarmThread::~BUS_DpAlarmThread()
{
    isRun = false;
    wait();
}

void BUS_DpAlarmThread::initFunSLot()
{
    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void BUS_DpAlarmThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

int BUS_DpAlarmThread::alarmDataUnit(sDataUnit &unit, bool cr)
{
    if((unit.value < unit.min) || (unit.value > unit.max))
    {
        if(unit.alarm == 0)
            unit.alarm = 1;
    } else
        unit.alarm = 0;

    if(cr) {
        if((unit.value < unit.crMin) || (unit.value > unit.crMax))
        {
            if(unit.crAlarm == 0)
                unit.crAlarm = 1;
        } else
            unit.crAlarm = 0;
    }

    return  unit.alarm;
}

void BUS_DpAlarmThread::boxAlarm(sDataPacket &box)
{
    int alarm = 0;
    if(box.offLine > 0)
    {
        int num = box.data.loopNum;
        for(int i=0; i<num; ++i) {
            sObjData *obj = &(box.data.loop[i]);
            alarm += alarmDataUnit(obj->cur); // 回路是否有告警
            alarm += alarmDataUnit(obj->vol);
        }

        for(int i=0; i<3; ++i) {
            sDataUnit *unit = &(box.data.env.tem[i]);
            alarm += alarmDataUnit(*unit);
        }
    }

     box.alarm = alarm;
}

void BUS_DpAlarmThread::busAlarm(sDevPackets *bus)
{
    for(int i=0; i<=bus->devNum; ++i) {
        boxAlarm(bus->dev[i]);
    }
}

void BUS_DpAlarmThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        for(int i=0; i<BUS_NUM; ++i) {
            sDevPackets *bus = BUS_DataPackets::bulid()->getBus(i);
            busAlarm(bus);
        }

        isRun  = false;
    }
}
