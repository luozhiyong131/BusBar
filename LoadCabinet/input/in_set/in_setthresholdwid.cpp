/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_setthresholdwid.h"
#include "ui_in_setthresholdwid.h"
#include "in_rtu/in_rtuthread.h"
#include "box/msgbox.h"

IN_SetThresholdWid::IN_SetThresholdWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_SetThresholdWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    QTimer::singleShot(2500,this,SLOT(on_updateBtn_clicked())); //延时初始化
}

IN_SetThresholdWid::~IN_SetThresholdWid()
{
    delete ui;
}


void IN_SetThresholdWid::initWidget()
{
    int addr = ui->addrBox->currentIndex() +1;
    sDataPacket *packet = IN_DataPackets::bulid()->getDev(addr);

    int id = ui->lineBox->currentIndex();
    sObjData *obj = &(packet->data.input[id]);

    ui->volMinBox->setValue(obj->vol.min);
    ui->volMaxBox->setValue(obj->vol.max);

    ui->curMinBox->setValue(obj->cur.min);
    ui->curMaxBox->setValue(obj->cur.max);
}

void IN_SetThresholdWid::on_addrBox_currentIndexChanged(int index)
{
    initWidget();
}

void IN_SetThresholdWid::on_lineBox_currentIndexChanged(int index)
{
    initWidget();
}

void IN_SetThresholdWid::on_updateBtn_clicked()
{
    initWidget();
}


void IN_SetThresholdWid::sendCmd()
{
    sRtuSentCom cmd;
    cmd.addr = ui->addrBox->currentIndex() + 1;
    if(ui->checkBox->isChecked()) cmd.addr = 0xff;

    int id = ui->lineBox->currentIndex();
    cmd.reg = 0x1002 + id *2;
    cmd.len = ui->volMaxBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);

    cmd.reg += 1;
    cmd.len = ui->volMinBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);

    cmd.reg = 0x1020 + id *2;
    cmd.len = ui->curMaxBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);

    cmd.reg += 1;
    cmd.len = ui->curMinBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);
}

void IN_SetThresholdWid::on_setBtn_clicked()
{
    QuMsgBox box(this, tr("确定要修改阈值？？"));
    if(box.Exec())    {
        sendCmd();
        QTimer::singleShot(12500,this,SLOT(on_updateBtn_clicked())); //延时初始化
        InfoMsgBox msg(this, tr("需要十秒数据才能重新刷新!!"));
    }
}
