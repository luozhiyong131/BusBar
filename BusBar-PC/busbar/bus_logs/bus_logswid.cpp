/*
 * logswid.cpp
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "bus_logswid.h"
#include "ui_bus_logswid.h"

BUS_LogsWid::BUS_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_LogsWid)
{
    ui->setupUi(this);

    initWidget();
}

BUS_LogsWid::~BUS_LogsWid()
{
    delete ui;
}

void BUS_LogsWid::initWidget()
{
    mMainEleWid = new BUS_LogLineEleWid(ui->stackedWid);  //主路电量
    ui->stackedWid->addWidget(mMainEleWid);
    connect(this, SIGNAL(busChangedSig(int)), mMainEleWid, SLOT(setTableSlot(int)));

    mBranchEleWid = new BUS_LogBranchEleWid(ui->stackedWid); //支路电量
    ui->stackedWid->addWidget(mBranchEleWid);
    connect(this, SIGNAL(busChangedSig(int)), mBranchEleWid, SLOT(setTableSlot(int)));

    mAlarmWid = new BUS_LogAlarmWid(ui->stackedWid); //告警
    ui->stackedWid->addWidget(mAlarmWid);
    connect(this, SIGNAL(busChangedSig(int)), mAlarmWid, SLOT(setTableSlot(int)));
}

void BUS_LogsWid::logTypeSlot(int type)
{
    switch (type) {
    case 0:
        ui->stackedWid->setCurrentWidget(mMainEleWid);
        break;
    case 1:
        ui->stackedWid->setCurrentWidget(mBranchEleWid);
        break;

    case 2:
        ui->stackedWid->setCurrentWidget(mAlarmWid);
        break;
    default:
        break;
    }
}


void BUS_LogsWid::on_lineBtn_clicked()
{
    logTypeSlot(0);
}

void BUS_LogsWid::on_loopBtn_clicked()
{
    logTypeSlot(1);
}

void BUS_LogsWid::on_alarmBtn_clicked()
{
    logTypeSlot(2);
}
