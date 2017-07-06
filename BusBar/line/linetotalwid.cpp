#include "linetotalwid.h"
#include "ui_linetotalwid.h"

LineTotalWid::LineTotalWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineTotalWid)
{
    ui->setupUi(this);

    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
}

LineTotalWid::~LineTotalWid()
{
    delete ui;
}


void LineTotalWid::initFunSLot()
{
    busChangeSlot(0);
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void LineTotalWid::busChangeSlot(int id)
{
    sDataPacket *shm = get_share_mem();
    mTgBus = &(shm->data[id].tgBus);
    updateData();
}

void LineTotalWid::timeoutDone()
{
    updateData();
}

void LineTotalWid::updateData()
{
    QString str = QString::number(mTgBus->vol) + "V";
    ui->tVolLab->setText(str);

    str =  QString::number(mTgBus->cur) + "A";
    ui->tCurLab->setText(str);

    str =  QString::number(mTgBus->pow) + "KW";
    ui->tPowLab->setText(str);

    str =  QString::number(mTgBus->apPow) + "KVA";
    ui->tApPowLab->setText(str);

    str =  QString::number(mTgBus->ele) + "KWh";
    ui->tEleLab->setText(str);
}
