/*
 * dptgthread.cpp
 * 数据统计
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "dptgthread.h"

DpTgThread::DpTgThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_dev_dataPacket(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(5*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

DpTgThread::~DpTgThread()
{
    isRun = false;
    wait();
}

void DpTgThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}


/**
 * @brief 获取平均数据 0视无效数据
 * @param data
 */
int DpTgThread::averData(int *data, int len)
{
    int size=0, value=0,temp;

    for(int i=0; i< len; ++i)
    {
        temp = data[i];
        if(temp > 0) {
            size++;
            value += temp;
        } else
            temp = 0;
    }

    if(size > 0)
        value /= size;

    return value;
}


void DpTgThread::tgObj(sObjData *obj, sTgObjData *tg)
{
    memset(tg, 0, sizeof(sTgObjData));
    for(int i=0; i<LINE_NUM; ++i)
    {
        tg->cur += obj->cur.value[i];
        tg->pow += obj->pow[i];
        tg->ele += obj->ele[i];
    }
    tg->vol = averData(obj->vol.value);
    tg->pf = averData(obj->pf);
}


void DpTgThread::tgDev(sDevData *dev)
{
    sObjData *data = &(dev->data);
    sTgObjData *tg = &(dev->tg);

    if(dev->offLine > 0) {
        tgObj(data, tg);
    } else {
        memset(data, 0, sizeof(sObjData));
        memset(&(dev->env), 0, sizeof(sEnvData));
        memset(&(dev->tg), 0, sizeof(sTgObjData));
    }
}

void DpTgThread::tgPacket(sDataPacket *packet)
{
    static int volData[DEV_NUM];
    memset(&(packet->tg), 0, sizeof(sTgObjData));

    for(int i=0; i<DEV_NUM; ++i) { // 插接箱统计
        sDevData *dev = &(packet->dev[i]);
        tgDev(dev);

        packet->tg.cur += dev->tg.cur;
        packet->tg.pow += dev->tg.pow;
        packet->tg.ele += dev->tg.ele;
        volData[i] = dev->tg.vol;
    }
    packet->tg.vol = averData(volData, DEV_NUM);
}


void DpTgThread::run()
{
    if(isRun == false)
    {
        isRun  = true;
        DpTgThread(shm);
        isRun  = false;
    }
}
