/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_setenvwid.h"
#include "ui_in_setenvwid.h"
#include "in_rtu/in_rtuthread.h"
#include "box/msgbox.h"

IN_SetEnvWid::IN_SetEnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_SetEnvWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    QTimer::singleShot(2500,this,SLOT(on_updateBtn_clicked())); //延时初始化
}

IN_SetEnvWid::~IN_SetEnvWid()
{
    delete ui;
}

void IN_SetEnvWid::initWidget()
{
    int addr = ui->addrBox->currentIndex() +1;
    sDataPacket *packet = IN_DataPackets::bulid()->getDev(addr);

    int id = ui->envBox->currentIndex();
    sDataUnit *tem = &(packet->data.env.tem[id]);

    ui->minBox->setValue(tem->min);
    ui->maxBox->setValue(tem->max);
}


void IN_SetEnvWid::on_addrBox_currentIndexChanged(int index)
{
    initWidget();
}

void IN_SetEnvWid::on_envBox_currentIndexChanged(int index)
{
    initWidget();
}

void IN_SetEnvWid::on_updateBtn_clicked()
{
    initWidget();
}

void IN_SetEnvWid::sendCmd()
{
    sRtuSentCom cmd;
    cmd.addr = ui->addrBox->currentIndex() + 1;
    if(ui->checkBox->isChecked()) cmd.addr = 0xff;

    int id = ui->envBox->currentIndex();
    cmd.reg = 0x1032 + id *2;
    cmd.len = ui->maxBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);

    cmd.reg += 1;
    cmd.len = ui->minBox->value();
    IN_RtuThread::bulid()->sentCmd(cmd);
}

void IN_SetEnvWid::on_setBtn_clicked()
{
    QuMsgBox box(this, tr("确定要修改阈值？？"));
    if(box.Exec())    {
        sendCmd();
        QTimer::singleShot(12500,this,SLOT(on_updateBtn_clicked())); //延时初始化
        InfoMsgBox msg(this, tr("需要十秒数据才能重新刷新!!"));
    }
}
