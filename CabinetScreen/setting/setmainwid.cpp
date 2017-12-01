/*
 * 设备设备主界面
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "setmainwid.h"
#include "ui_setmainwid.h"

SetMainWid::SetMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetMainWid)
{
    ui->setupUi(this);

   // ui->widget->setStyleSheet("background-color:#66ccff;");
    mDevWid[0] = new DevThresholdWid(ui->widget_1);
    mDevWid[0]->setType("A");
    mDevWid[1] = new DevThresholdWid(ui->widget_2);
    mDevWid[1]->setType("B");

    QGridLayout *yout_1 = new QGridLayout(ui->widget_1);
    yout_1->addWidget(mDevWid[0]);
    yout_1->setContentsMargins(20,0,0,0);
    QGridLayout *yout_2 = new QGridLayout(ui->widget_2);
    yout_2->addWidget(mDevWid[1]);
    yout_2->setContentsMargins(0,0,20,0);

    for(int i=0; i<DEV_NUM; i++) {
        mDevWid[i]->init(i);
    }
}

SetMainWid::~SetMainWid()
{
    delete ui;
}
