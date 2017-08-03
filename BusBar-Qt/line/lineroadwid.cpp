#include "lineroadwid.h"
#include "ui_lineroadwid.h"
#include "interfacechangesig.h"

LineRoadWid::LineRoadWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineRoadWid)
{
    ui->setupUi(this);

    isRun = false;
    initLine(0);
    busChangeSlot(0);
    timer = new QTimer(this);
    timer->start(3*1000 + rand() % 100);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));
}

LineRoadWid::~LineRoadWid()
{
    delete ui;
}

void LineRoadWid::initLine(int id)
{
    mID = id;
}


void LineRoadWid::interfaceChangedSlot(int id)
{
    if(id == 2) {
        isRun = true;
    } else {
        isRun = false;
    }
}

void LineRoadWid::busChangeSlot(int id)
{    
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[id].data);
    updateData();
}

void LineRoadWid::timeoutDone()
{
    if(isRun) {
        updateData();
    }
}


void LineRoadWid::updateAlarmStatus(QLabel *lab, sDataUnit &unit)
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


void LineRoadWid::updateData()
{
    int id = mID;
    QString str = "L" + QString::number(id+1);
    ui->name->setText(str);

    str = QString::number(mData->vol.value[id]) + "V";
    ui->volLab->setText(str);
    updateAlarmStatus(ui->volLab, mData->vol);

    str =  QString::number(mData->cur.value[id]/COM_RATE_CUR,'f',1) + "A";
    ui->curLab->setText(str);
    updateAlarmStatus(ui->curLab, mData->cur);

    str =  QString::number(mData->cur.max[id]/COM_RATE_CUR,'f',1) + "A";
    ui->maxCur->setText(str);

    str =  QString::number(mData->apPow[id]/COM_RATE_POW,'f',1) + "kVA";
    ui->apPow->setText(str);

    str =  QString::number(mData->pow[id]/COM_RATE_POW,'f',1) + "kW";
    ui->powLab->setText(str);

    str =  QString::number(mData->pf[id]/COM_RATE_PF, 'f',2);
    ui->pfLab->setText(str);

    str =  QString::number(mData->ele[id]/COM_RATE_ELE,'f',1) + "kWh";
    ui->eleLab->setText(str);
}
