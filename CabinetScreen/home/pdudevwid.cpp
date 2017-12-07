/*
 * 设备显示界面
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "pdudevwid.h"
#include "ui_pdudevwid.h"

PduDevWid::PduDevWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PduDevWid)
{
    ui->setupUi(this);

    mLine = 0;
    init(0);
    initWid();

    ui->comboBox->setHidden(true);
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

   // ui->groupBox->setAttribute(Qt::WA_TranslucentBackground, true);
  //  ui->groupBox->setStyleSheet("QGroupBox{background: #EEF9FF}");
    //去掉多余的label
    ui->label_6->hide();
    ui->label_7->hide();
    ui->tmpLab->hide();
    ui->humLab->hide();
}

PduDevWid::~PduDevWid()
{
    delete ui;
}

/**
 * @brief 初始化数据，
 * @param id 设备号
 */
void PduDevWid::init(int id)
{
    sDataPacket *packet = get_dev_dataPacket();
    mDevData = &(packet->dev[id]);
}

void PduDevWid::setType(QString type)
{
    ui->label_5->setText(type);
}

/**
 * @brief 初始化界面
 */
void PduDevWid::initWid()
{
    QString str = "---";
    ui->volLcd->display(str);
    ui->curLcd->display(str);
    ui->powLcd->display(str);
    ui->eleLab->setText(str);
    ui->tmpLab->setText(str);
    ui->humLab->setText(str);
}

/**
 * @brief 检查报警 显示颜色显示
 * @param line
 */
void PduDevWid::checkAlarm(int line)
{
    int alarm = mDevData->data.vol.alarm[line];
    if(alarm) {
        ui->volLcd->setStyleSheet("color: rgb(255, 0, 0);");
    } else {
        ui->volLcd->setStyleSheet("color:black;");
    }

    alarm = mDevData->data.cur.alarm[line];
    if(alarm) {
        ui->curLcd->setStyleSheet("color: rgb(255, 0, 0);");
    } else {
        ui->curLcd->setStyleSheet("color:black;");
    }
}


/**
 * @brief 界面数据更新
 * @param line
 */
void PduDevWid::updateWid(int line)
{
    double value = mDevData->data.vol.value[line] / COM_RATE_VOL;
    ui->volLcd->display(value);

    value = mDevData->data.cur.value[line] / COM_RATE_CUR;
    ui->curLcd->display(value);

    value = mDevData->data.pow[line] / COM_RATE_POW;
    ui->powLcd->display(value);

    value = mDevData->data.ele[line] / COM_RATE_ELE;
    QString str = QString::number(value,'f', 1);
    ui->eleLab->setText(str);

    value = mDevData->env.tem.value[line] / COM_RATE_TEM;
    str = QString::number(value) + " ℃";
    ui->tmpLab->setText(str);

    value = mDevData->env.hum.value[line] / COM_RATE_HUM;
    str = QString::number(value) + " %";
    ui->humLab->setText(str);
}

/**
 * @brief 定时方法角发
 */
void PduDevWid::timeoutDone()
{
    if(mDevData->offLine > 0) {
        int line = mLine;
        updateWid(line);
        checkAlarm(line);
    } else {
        initWid();
    }
}

/**
 * @brief 相切换
 * @param index
 */
void PduDevWid::on_comboBox_currentIndexChanged(int index)
{
    mLine = index;
    timeoutDone();
}
