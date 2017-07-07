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

static QMutex mutex; // 互拆锁
static QString gEmailStr; // 报警邮件的内容
static QStringList gAlarmStr; // 实时报警内容 存储格式 母线名称，报警类型，报警内容

/**
 * @brief 获取报警邮件的内容
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
 * @brief 获取实时报警内容
 * @return  实时报警内容 存储格式 母线名称，报警类型，报警内容
 */
QStringList get_alarm_str()
{
    QMutexLocker locker(&mutex);
    QStringList str = gAlarmStr;
    gAlarmStr.clear();

    return str;
}


DpAlarmSlave::DpAlarmSlave(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_share_mem(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(3*1000);
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
    db_alarm_obj(mBusId)->insertItem(item);
    msleep(5);

    QMutexLocker locker(&mutex);
    gEmailStr += "\t" + typeStr + "\t" +str + "\n"; //邮件发送内容
}


void DpAlarmSlave::unitAlarm(QString &typeStr, QString &msg, sDataUnit &unit, double rate, const QString &sym)
{
    for(int i=0; i<3; ++i)
    {
        QString str = msg;
        if(unit.alarm[i])
        {
            typeStr += tr("报警");
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
            typeStr += tr("预警");
            str += tr("%1，当前值：%2%3, 临界下限值：%4%5, 临界上限值：%6%7").arg(i+1)
                    .arg(unit.value[i]/rate).arg(sym)
                    .arg(unit.crMin[i]/rate).arg(sym)
                    .arg(unit.crMax[i]/rate).arg(sym);
        }

        // 实时报警信息
        if((unit.alarm[i]) || (unit.crAlarm[i])) {
            mAlarmStr << shm->data[mBusId].busName;
            mAlarmStr << typeStr;
            mAlarmStr << str;
        }
    }
}


void DpAlarmSlave::boxAlarm(sBoxData &box)
{
    if(box.boxAlarm)
    {
        QString typeStr = tr("回路电流");
        if(box.boxCurAlarm) {
            QString msg = tr("插接箱：%1，回路").arg(box.boxName);
            unitAlarm(typeStr, msg, box.data.cur, 10, "A");
        }

        typeStr = tr("接插箱温度");
        if(box.boxEnvAlarm) {
            QString msg = tr("插接箱：%1，温度").arg(box.boxName);
            unitAlarm(typeStr, msg, box.env.tem, 10, "C");
        }
    }
}



void DpAlarmSlave::busAlarm(int id)
{
    mBusId = id;
    sBusData *bus = &(shm->data[id]);
    if(bus->busAlarm) {
        if(bus->busCurAlarm) { // 总线电流报警
            QString typeStr = tr("主路电流");
            QString msg = tr("母线：%1，Line ").arg(bus->busName);
            unitAlarm(typeStr, msg, bus->data.cur, 10, "A");
        }

        if(bus->busVolAlarm) { // 总线电压报警
            QString typeStr = tr("主路电压");
            QString msg = tr("母线：%1，Line ").arg(bus->busName);
            unitAlarm(typeStr, msg, bus->data.vol, 10, "V");
        }

        if(bus->busEnvAlarm) { // 温度
            QString typeStr = tr("主路湿度");
            QString msg = tr("母线：%1，温度").arg(bus->busName);
            unitAlarm(typeStr, msg, bus->env.tem, 10, "C");
        }
    }

    for(int i=1; i<=bus->boxNum; ++i) {
        boxAlarm(bus->box[i]);
    }
}

void DpAlarmSlave::checkAlarm()
{
    for(int i=0; i<BUS_NUM; ++i)
        busAlarm(i);

    QMutexLocker locker(&mutex);
    gAlarmStr = mAlarmStr;
    mAlarmStr.clear();
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
