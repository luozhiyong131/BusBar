/*
 * dpalarmslave.cpp
 * 报警内容保存，报警信息提示线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "dpalarmslave.h"
#include "dbalarm.h"


DpAlarmSlave::DpAlarmSlave(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_dev_dataPacket(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(5*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


DpAlarmSlave::~DpAlarmSlave()
{
    isRun = false;
    wait();
}

void DpAlarmSlave::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}


void DpAlarmSlave::saveMsg(const QString &typeStr, const QString &str)
{
    DbAlarmItem item;
    item.type = typeStr;
    item.msg = str;
    DbAlarm::bulid()->insertItem(item);
    msleep(5);
}


void DpAlarmSlave::unitAlarm(QString &typeStr, QString &msg, sDataUnit &unit, double rate, const QString &sym)
{
    for(int i=0; i<LINE_NUM; ++i)
    {
        QString str=msg, tempStr = typeStr;
        if(unit.alarm[i])
        {
            tempStr = typeStr + tr("报警");
            str += tr("%1，当前值：%2%3, 最小值：%4%5, 最大值：%6%7").arg(i+1)
                    .arg(unit.value[i]/rate).arg(sym)
                    .arg(unit.min[i]/rate).arg(sym)
                    .arg(unit.max[i]/rate).arg(sym);

            if(unit.alarm[i] == 1){
                unit.alarm[i] = 2;
                saveMsg(typeStr, str);
            }
        }
        else if(unit.crAlarm[i])
        {
            tempStr = typeStr +  tr("预警");
            str += tr("%1，当前值：%2%3, 临界下限值：%4%5, 临界上限值：%6%7").arg(i+1)
                    .arg(unit.value[i]/rate).arg(sym)
                    .arg(unit.crMin[i]/rate).arg(sym)
                    .arg(unit.crMax[i]/rate).arg(sym);
        }
    }
}


void DpAlarmSlave::devAlarm(int id)
{
    sDevData *dev = &(shm->dev[id]);

    if(dev->alarm) {
        QString str = tr("PDU %1 ").arg(id+1);
        if(dev->curAlarm) { // 总线电流报警
            QString typeStr = str + tr("电流");
            QString msg = tr("Line ");
            unitAlarm(typeStr, msg, dev->data.cur, 10, "A");
        }

        if(dev->volAlarm) { // 总线电压报警
            QString typeStr = str + tr("电压");
            QString msg = tr("Line ");
            unitAlarm(typeStr, msg, dev->data.vol, 10, "V");
        }

        if(dev->temAlarm) { // 温度
            QString typeStr = str + tr("湿度");
            QString msg = tr("温度");
            unitAlarm(typeStr, msg, dev->env.tem, 10, " ℃");
        }

        if(dev->humAlarm) { // 温度
            QString typeStr = str + tr("湿度");
            QString msg = tr("温度");
            unitAlarm(typeStr, msg, dev->env.hum, 10, " %");
        }
    }

}

void DpAlarmSlave::checkAlarm()
{
    for(int i=0; i<DEV_NUM; ++i)
        devAlarm(i);
}

void DpAlarmSlave::run()
{
    if(isRun == false)
    {
        isRun  = true;
        checkAlarm();
        isRun  = false;
    }
}
