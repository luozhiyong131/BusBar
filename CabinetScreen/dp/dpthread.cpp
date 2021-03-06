/*
 * dpthread.cpp
 * 数据处理线程入口
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "dpthread.h"

DpThread::DpThread(QObject *parent) : QThread(parent)
{
    mTgThread = new DpTgThread(this);
    mAlarmThread = new DpAlarmThread(this);
    mEle = new DpEleSlaveThread(this);
    mAlarmSlave = new DpAlarmSlave(this);
    mDevSpied = new DpDevSpied(this);
}

DpThread::~DpThread()
{

}








