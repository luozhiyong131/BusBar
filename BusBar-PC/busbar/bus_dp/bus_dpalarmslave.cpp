/*
 * dpalarmslave.cpp
 * 告警内容保存，告警信息提示线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "bus_dpalarmslave.h"
#include "dbalarm.h"

static QMutex mutex; // 互拆锁
static QString gEmailStr; // 告警邮件的内容
static QStringList gAlarmStr; // 实时告警内容 存储格式 母线名称，告警类型，告警内容

/**
 * @brief 获取告警邮件的内容
 * @return
 */
QString get_email_str()
{
    QMutexLocker locker(&mutex);
    QString str = gEmailStr;
    gEmailStr.clear();

    return str;
}

/**
 * @brief 获取实时告警内容
 * @return  实时告警内容 存储格式 母线名称，告警类型，告警内容
 */
QStringList get_alarm_str()
{
    QMutexLocker locker(&mutex);
    QStringList str = gAlarmStr;
    gAlarmStr.clear();

    return str;
}

int get_alarm_len()
{
    return gAlarmStr.size();
}


BUS_DpAlarmSlave::BUS_DpAlarmSlave(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = BUS_DataPackets::bulid(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(5*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


BUS_DpAlarmSlave::~BUS_DpAlarmSlave()
{
    isRun = false;
    wait();
}

void BUS_DpAlarmSlave::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}


void BUS_DpAlarmSlave::saveMsg(const QString &typeStr, const QString &str)
{
    BUS_DbAlarmItem item;
    item.type = typeStr;
    item.msg = str;
    bus_alarm_db(mBusId)->insertItem(item);
    msleep(5);

    QMutexLocker locker(&mutex);
    gEmailStr += "\t" + typeStr + "\t" +str + "\n"; //邮件发送内容
}


void BUS_DpAlarmSlave::unitAlarm(const QString &nameStr, QString &typeStr, QString &msg,
                             sDataUnit &unit, double rate, const QString &sym)
{
    QString str=msg, tempStr = typeStr;
    if(unit.alarm)
    {
        tempStr = typeStr + tr("告警");
        str += tr("%1，当前值：%2%3, 最小值：%4%5, 最大值：%6%7").arg(nameStr)
                .arg(unit.value/rate).arg(sym)
                .arg(unit.min/rate).arg(sym)
                .arg(unit.max/rate).arg(sym);

        if(unit.alarm == 1){
            unit.alarm = 2;
            saveMsg(typeStr, str);
        }
    }
    else if(unit.crAlarm)
    {
        tempStr = typeStr +  tr("预警");
        str += tr("%1，当前值：%2%3, 临界下限值：%4%5, 临界上限值：%6%7").arg(nameStr)
                .arg(unit.value/rate).arg(sym)
                .arg(unit.crMin/rate).arg(sym)
                .arg(unit.crMax/rate).arg(sym);
    }

    // 实时告警信息
    if((unit.alarm) || (unit.crAlarm)) {
        mAlarmStr << shm->getBox(mBusId,0)->name;
        mAlarmStr << tempStr;
        mAlarmStr << str;
    }
}

void BUS_DpAlarmSlave::boxAlarm(sDataPacket &box)
{
    if(box.offLine) {
        if(box.alarm)  {
            QString msg = tr("插接箱：%1，").arg(box.name);

            for(int i=0; i<box.data.loopNum; ++i) {
                sObjData *obj = &(box.data.loop[i]);
                QString typeStr = tr("回路电流");
                unitAlarm(obj->name,  typeStr, msg, obj->cur, COM_RATE_CUR, "A");

                typeStr = tr("回路电压");
                unitAlarm(obj->name, typeStr, msg, obj->vol, COM_RATE_VOL, "V");

                if(i < box.data.env.envNum) {
                    typeStr = tr("插接箱温度");
                    unitAlarm(obj->name, typeStr, msg, box.data.env.tem[i], COM_RATE_TEM, "°C");
                }
            }
        }
    } else {
        mAlarmStr << shm->getBox(mBusId,0)->name;
        mAlarmStr << tr("插接箱离线");
        mAlarmStr << tr("插接箱：%1 已离线").arg(box.name);
    }
}

void BUS_DpAlarmSlave::busAlarm(int id)
{
    mBusId = id;
    sDataPacket *bus = shm->getBox(id, 0);

    if(bus->alarm)
    {
        for(int i=0; i<bus->data.loopNum; ++i) {
            sObjData *obj = &(bus->data.loop[i]);
            QString typeStr = tr("主路电流");
            QString msg = tr("母线：%1 ").arg(bus->name);
            QString alarmStr = tr("输入 %1").arg(i+1);

            unitAlarm(alarmStr, typeStr, msg, obj->cur, COM_RATE_CUR, "A");

            typeStr = tr("主路电压");
            unitAlarm(alarmStr, typeStr, msg, obj->vol, COM_RATE_VOL, "V");

            typeStr = tr("主路温度");
            msg = tr("母线：%1，").arg(bus->name);
            alarmStr = tr("温度 %1").arg(i+1);
            unitAlarm(alarmStr, typeStr, msg, bus->data.env.tem[i], COM_RATE_TEM, "°C");
        }
    }

    sDevPackets *packets = shm->getBus(id);
    for(int i=1; i<=packets->devNum; ++i) {
        boxAlarm(packets->dev[i]);
    }
}

void BUS_DpAlarmSlave::checkAlarm()
{
    for(int i=0; i<BUS_NUM; ++i)
        busAlarm(i);

    QMutexLocker locker(&mutex);
    gAlarmStr = mAlarmStr;
    mAlarmStr.clear();
}

void BUS_DpAlarmSlave::run()
{
    if(isRun == false)
    {
        isRun  = true;
        checkAlarm();
        isRun  = false;
    }
}
