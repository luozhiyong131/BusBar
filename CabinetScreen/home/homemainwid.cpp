/*
 * home界面
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "homemainwid.h"
#include "ui_homemainwid.h"

HomeMainWid::HomeMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeMainWid)
{
    ui->setupUi(this);

    mDevWid[0] = new PduDevWid(ui->widget_1);
    mDevWid[1] = new PduDevWid(ui->widget_2);
    for(int i=0; i<2; ++i) mDevWid[i]->init(i);
}

HomeMainWid::~HomeMainWid()
{
    delete ui;
}
