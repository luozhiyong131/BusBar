/*
 * dpeleslavethread.cpp
 * 电能数据保存线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "dpeleslavethread.h"
#include "dbdevele.h"

DpEleSlaveThread::DpEleSlaveThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_dev_dataPacket(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(60*60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


DpEleSlaveThread::~DpEleSlaveThread()
{
    isRun = false;
    wait();
}

void DpEleSlaveThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

void DpEleSlaveThread::saveDev(int id, sDevData  &dev)
{
    if(dev.offLine == 0) return; //不保存
    sTgObjData *tg = &(dev.tg);

    DbDevEleItem item;
    item.name = "PDU " + QString::number(id+1);
    item.vol = tg->vol/COM_RATE_VOL;
    item.cur = tg->cur/COM_RATE_CUR;
    item.pow = tg->pow/COM_RATE_POW;
    item.ele = tg->ele/COM_RATE_ELE;

    DbDevEle::bulid()->insertItem(item);
    msleep(5);
}


void DpEleSlaveThread::saveCab()
{
    if(shm->tg.vol == 0) return; //不保存
    sTgObjData *tg = &(shm->tg);

    DbCabEleItem item;
    item.vol = tg->vol/COM_RATE_VOL;
    item.cur = tg->cur/COM_RATE_CUR;
    item.pow = tg->pow/COM_RATE_POW;
    item.ele = tg->ele/COM_RATE_ELE;
    DbCabEle::bulid()->insertItem(item);
    msleep(5);

    for(int i=0; i<DEV_NUM; ++i)
        saveDev(i, shm->dev[i]);
}


void DpEleSlaveThread::run()
{
    if(isRun == false)
    {
        isRun  = true;
        saveCab();
        isRun  = false;
    }
}
