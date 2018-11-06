/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_setmainwid.h"
#include "ui_in_setmainwid.h"
IN_setMainWid::IN_setMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_setMainWid)
{
    ui->setupUi(this);

    mSetEnvWid = new IN_SetEnvWid(ui->widget_2) ;
    mSetThresholdWid = new IN_SetThresholdWid(ui->widget_1);
}

IN_setMainWid::~IN_setMainWid()
{
    delete ui;
}
