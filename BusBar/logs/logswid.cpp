/*
 * logswid.cpp
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "logswid.h"
#include "ui_logswid.h"

LogsWid::LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogsWid)
{
    ui->setupUi(this);

    initWidget();
}

LogsWid::~LogsWid()
{
    delete ui;
}


void LogsWid::initWidget()
{
    mMainEleWid = new LogMainEleWid(ui->stackedWid);
    ui->stackedWid->addWidget(mMainEleWid);

    mBranchEleWid = new LogBranchEleWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBranchEleWid);

    mAlarmWid = new LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mAlarmWid);
}

void LogsWid::on_lineBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mMainEleWid);
}

void LogsWid::on_branchBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBranchEleWid);
}

void LogsWid::on_alarmBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mAlarmWid);
}
