/*
 * dpeleslavethread.cpp
 * 电能数据保存线程
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "bus_dpeleslavethread.h"
#include "bus_sql/bus_dblineele.h"

BUS_DpEleSlaveThread::BUS_DpEleSlaveThread(QObject *parent) : QThread(parent)
{
    isRun = false;

    timer = new QTimer(this);
    timer->start(4*60*60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BUS_DpEleSlaveThread::~BUS_DpEleSlaveThread()
{
    isRun = false;
    wait();
}

void BUS_DpEleSlaveThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

void BUS_DpEleSlaveThread::saveBox(int bus, sDataPacket  &box)
{
    double rate = 10;
    if(box.offLine == 0) return; //不保存

    DbBranchEleItem item;
    item.name = box.name;
    for(int i=0; i<9; ++i) {
        item.loops[i] = box.data.loop[i].ele/rate;
    }
    item.loop = box.data.tg.ele/rate;

    bus_branchEle_db(bus)->insertItem(item);
    msleep(50);
}

void BUS_DpEleSlaveThread::saveBus(int id)
{
    int line = 0;
    double rate = 10;

    sDevPackets *bus = BUS_DataPackets::bulid()->getBus(id);
    sDataPacket *busBox = &(bus->dev[0]);
    if(busBox->data.tg.vol.value == 0) return; //不保存

    uint ele[LOOP_NUM]={0};
    for(int i=0; i<LOOP_NUM; ++i)
        ele[i] = busBox->data.loop[i].ele;

    DbLineEleItem item;
    item.line_1 = ele[line++]/rate;
    item.line_2 = ele[line++]/rate;
    item.line_3 = ele[line++]/rate;
    item.line = busBox->data.tg.ele/rate;

    bus_lineEle_db(id)->insertItem(item);
    msleep(50);

    static int count=0;
    if(count++ % 24 == 0)  {
        for(int i=1; i<=bus->devNum; ++i)
            saveBox(id, bus->dev[i]);
    }
}

void BUS_DpEleSlaveThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        for(int i=0; i<BUS_NUM; ++i)
            saveBus(i);

        isRun  = false;
    }
}
