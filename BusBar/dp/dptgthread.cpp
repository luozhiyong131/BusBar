/*
 * dptgthread.cpp
 * 数据统计
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "dptgthread.h"

DpTgThread::DpTgThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_share_mem(); // 获取共享内存

    timer = new QTimer(this);
    timer->start(3*1000);
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
    for(int i=0; i<3; ++i)
    {
        tg->cur += obj->cur.value[i];
        tg->pow += obj->pow[i];
        tg->ele += obj->ele[i];
        tg->apPow += obj->apPow[i];
    }
    tg->vol = averData(obj->vol.value);
    tg->pf = averData(obj->pf);
}


void DpTgThread::tgBox(sBoxData *box)
{
    sObjData *loop = &(box->data);
    sTgObjData *tgBox = &(box->tgBox);

    if(box->offLine)
        tgObj(loop, tgBox);
}

/**
 * @brief 工业母线相统计 *
 * @param bus
 */
void DpTgThread::tgBusLine(sBusData *bus)
{
    static int vol[BOX_NUM], pf[BOX_NUM];
    sObjData *tg = &(bus->data);

    // A\B\C三相分别从输出位1、2、3统计
    memset(tg, 0, sizeof(sTgObjData));
    for(int i=0; i<3; ++i)
    {
        int len = 0;
        for(int k=0; k<bus->boxNum; ++k)
        {
            sBoxData *box = &(bus->box[k]);
            if(box->offLine <= 0) continue;
            len++;

            sObjData *obj = &(bus->box[k].data);
            tg->cur.value[i] += obj->cur.value[i];
            tg->pow[i] += obj->pow[i];
            tg->ele[i] += obj->ele[i];
            tg->apPow[i] += obj->apPow[i];

            vol[k] = obj->vol.value[i];
            pf[k] = obj->pf[i];
        }
        tg->vol.value[i] = averData(vol, len);
        tg->pf[i] = averData(pf, len);
    }
}

void DpTgThread::tgBus(sBusData *bus)
{
    for(int i=0; i<bus->boxNum; ++i) { // 插接箱统计
        tgBox(&(bus->box[i]));
    }
    tgBusLine(bus);

    tgObj(&(bus->data), &(bus->tgBus));
}


void DpTgThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        for(int i=0; i<BUS_NUM; ++i)
            tgBus(&(shm->data[i]));

        isRun  = false;
    }
}
