/*
 * dpthread.cpp
 * 数据处理线程入口
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "bus_dpthread.h"

BUS_DpThread::BUS_DpThread(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(5*1000,this,SLOT(initFunSLot())); //延时初始化
}

BUS_DpThread::~BUS_DpThread()
{

}


void BUS_DpThread::initFunSLot()
{
    mTgThread = new BUS_DpTgThread(this);
    mAlarmThread = new BUS_DpAlarmThread(this);
    mEle = new BUS_DpEleSlaveThread(this);
    mAlarmSlave = new BUS_DpAlarmSlave(this);
}





