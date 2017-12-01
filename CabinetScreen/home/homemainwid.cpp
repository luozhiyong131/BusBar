/*
 * home界面
 *
 *  Created on: 2017年10月11日
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
    mDevWid[0]->setType("A");
    mDevWid[1] = new PduDevWid(ui->widget_2);
    mDevWid[1]->setType("B");

    QGridLayout *yout_1 = new QGridLayout(ui->widget_1);
    yout_1->addWidget(mDevWid[0]);
    yout_1->setContentsMargins(20,0,0,0);
    QGridLayout *yout_2 = new QGridLayout(ui->widget_2);
    yout_2->addWidget(mDevWid[1]);
    yout_2->setContentsMargins(0,0,20,0);


    for(int i=0; i<2; ++i) mDevWid[i]->init(i);
}

HomeMainWid::~HomeMainWid()
{
    delete ui;
}
