/*
 * dptgthread.cpp
 * 数据统计
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "bus_dptgthread.h"

BUS_DpTgThread::BUS_DpTgThread(QObject *parent) : QThread(parent)
{
    isRun = false;

    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BUS_DpTgThread::~BUS_DpTgThread()
{
    isRun = false;
    wait();
}

void BUS_DpTgThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}


/**
 * @brief 获取平均数据 0视无效数据
 * @param data
 */
int BUS_DpTgThread::averData(int *data, int len)
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

void BUS_DpTgThread::initData(sObjData *tg)
{
    tg->vol.value = 0; // 电压
    tg->cur.value = 0; // 电流

    tg->pow = 0; // 功率
    tg->ele = 0; // 电能

    tg->pf = 0; // 功率因素
    tg->activePow = 0; // 有功功率值
}

void BUS_DpTgThread::tgObj(sDevData &dev)
{
    sObjData *tg = &(dev.tg);
    initData(tg);

    int array[LOOP_NUM] = {0};
    for(int i=0; i<dev.loopNum; ++i)
    {
        sObjData *obj = &(dev.loop[i]);
        array[i] = obj->vol.value;
        tg->cur.alarm += obj->cur.value;
        tg->pow += obj->pow;
        tg->ele += obj->ele;
        tg->activePow += obj->activePow;
    }

    tg->vol.value = averData(array);
    if(tg->activePow > 0)
        tg->pf = (tg->pow * 100.0 / tg->activePow);
    else
        tg->pf = 0;
    if(tg->pf>99) tg->pf = 99;
}


void BUS_DpTgThread::lineTgObj(sDevData &dev)
{
    int num = 0;
    for(int i=0; i<3; ++i)
    {
        sObjData *tg = &(dev.line[i]);
        initData(tg);
        // tg->vol = dev.loop[i].vol.value;
        for(int j=0; j<3; ++j) {
            sObjData *obj = &(dev.loop[i+j*3]);
            tg->cur.value += obj->cur.value;
            tg->pow += obj->pow;
            tg->ele += obj->ele;
            tg->activePow += obj->cur.value * obj->vol.value/10;
            int v = obj->vol.value;
            if(v) tg->vol.value = v;
        }
        if(tg->vol.value) num++;
    }
    dev.lineNum = num;

    for(int i=0; i<num; ++i) {
        sObjData *tg = &(dev.line[i]);
        if(tg->activePow > 0) tg->pf = (tg->pow * 100.0 / tg->activePow);
        else tg->pf = 0;
        if(tg->pf>99) tg->pf = 99;
        if(tg->pow > tg->activePow) tg->pow = tg->activePow;
    }
}


void BUS_DpTgThread::dcLineTgObj(sDevData &dev, int line, int len)
{
    int num = 0;

    if(len == 2 && line == 2)
    {
        for(int i = 0 ; i < 2; i++)
        {
            sObjData *tg = &(dev.line[i]);
            sObjData *obj = &(dev.loop[i]);

            tg->vol.value = obj->vol.value;
            tg->cur.value = obj->cur.value;
            tg->pow = obj->pow;
            tg->ele = obj->ele;
            tg->activePow = obj->activePow;

            if(tg->vol.value) num++;
        }
    }else{
        for(int i = 0 ; i < 2; i++){
            sObjData *tg = &(dev.line[i]);
            initData(tg);
            tg->vol.value = dev.loop[i].vol.value;
            if(tg->vol.value) num++;

            for(int j=0; j<2; ++j) {
                sObjData *obj = &(dev.loop[i*2+j]);
                tg->cur.value += obj->cur.value;
                tg->pow += obj->pow;
                tg->ele += obj->ele;
                tg->activePow += obj->activePow;
            }
        }
    }
    dev.lineNum = num;

    for(int i=0; i<num; ++i) {
        sObjData *tg = &(dev.line[i]);
        if(tg->activePow > 0)
            tg->pf = (tg->pow * 100.0 / tg->activePow);
        else
            tg->pf = 0;
        if(tg->pf>99) tg->pf = 99;
        if(tg->pow > tg->activePow) tg->pow = tg->activePow;
    }
}

void BUS_DpTgThread::tgBox(sDataPacket *box)
{
    if(box->offLine) {
        tgObj(box->data);
        if(box->dc) {
            lineTgObj(box->data);
        } else  {
            dcLineTgObj(box->data, box->hz, box->data.loopNum);
        }
    }
}

void BUS_DpTgThread::tgBus(sDevPackets *bus)
{
    for(int i=0; i<=bus->devNum; ++i) { // 插接箱统计
        tgBox(&(bus->dev[i]));
    }
}


void BUS_DpTgThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        for(int i=0; i<BUS_NUM; ++i) {
            sDevPackets *bus = BUS_DataPackets::bulid()->getBus(i);
            tgBus(bus);
        }

        isRun  = false;
    }
}
