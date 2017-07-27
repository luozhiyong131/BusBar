#include "boxloopwid.h"
#include "ui_boxloopwid.h"

BoxLoopWid::BoxLoopWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxLoopWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BoxLoopWid::~BoxLoopWid()
{
    delete ui;
}


void BoxLoopWid::initLine(int bus, int box, int id)
{
    mID = id;
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[bus].box[box].data);
    updateData();
}


void BoxLoopWid::timeoutDone()
{
    updateData();
}


void BoxLoopWid::updateAlarmStatus(QLabel *lab, sDataUnit &unit)
{
    int id = mID;
    QPalette pe;

    if(unit.alarm[id])
        pe.setColor(QPalette::WindowText,Qt::red);
    else  if(unit.crAlarm[id])
        pe.setColor(QPalette::WindowText,Qt::yellow);
    else
        pe.setColor(QPalette::WindowText,Qt::black);

    lab->setPalette(pe);
}


void BoxLoopWid::updateData()
{
    int id = mID;
    QString str = "Loop" + QString::number(id+1);
    ui->name->setText(str);

    int sw = mData->sw[id];
    if(sw)
        str = "开";
    else
        str = "关";
    ui->volLab->setText(str);

    str =  QString::number(mData->vol.value[id]) + "V";
    ui->curLab->setText(str);
    updateAlarmStatus(ui->volLab, mData->vol);

    str =  QString::number(mData->cur.value[id]) + "A";
    ui->maxCur->setText(str);
    updateAlarmStatus(ui->curLab, mData->cur);

    str =  QString::number(mData->apPow[id]) + "kVA";
    ui->apPow->setText(str);

    str =  QString::number(mData->pow[id]) + "kW";
    ui->powLab->setText(str);

    str =  QString::number(mData->ele[id]) + "kWh";
    ui->eleLab->setText(str);
}
