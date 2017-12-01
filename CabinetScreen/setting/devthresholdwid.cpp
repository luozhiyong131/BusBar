/*
 * 设备阈值界面
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "devthresholdwid.h"
#include "ui_devthresholdwid.h"

DevThresholdWid::DevThresholdWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevThresholdWid)
{
    ui->setupUi(this);

    mLine = 0;
    ui->comboBox->setHidden(true);

    mUnitWid[0] = new ThresholdUnitWid(ui->volWid);
    mUnitWid[1] = new ThresholdUnitWid(ui->curWid);
    mUnitWid[2] = new ThresholdUnitWid(ui->temWid);
    mUnitWid[3] = new ThresholdUnitWid(ui->humWid);

    //多余的界面
    ui->label_6->hide();
    ui->label_7->hide();
    ui->temWid->hide();
    ui->humWid->hide();
}

DevThresholdWid::~DevThresholdWid()
{
    delete ui;
}


void DevThresholdWid::init(int id)
{
    for(int i=0; i<4; ++i) {
        mUnitWid[i]->init(id, i, mLine);
    }
    mDevId = id;
}

void DevThresholdWid::setType(QString type)
{
    ui->label_8->setText(type);
}

void DevThresholdWid::on_comboBox_currentIndexChanged(int index)
{
    mLine = index;
    mUnitWid[mDevId]->setLine(mLine);
}
