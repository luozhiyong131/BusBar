#include "boxtotalwid.h"
#include "ui_boxtotalwid.h"

BoxTotalWid::BoxTotalWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxTotalWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BoxTotalWid::~BoxTotalWid()
{
    delete ui;
}


void BoxTotalWid::initFun(int bus, int box)
{
    sDataPacket *shm = get_share_mem();
    mTgBus = &(shm->data[bus].box[box].tgBox);
    updateData();
}

void BoxTotalWid::timeoutDone()
{
    updateData();
}

void BoxTotalWid::updateData()
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
