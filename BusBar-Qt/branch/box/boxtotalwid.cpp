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
    mTgBox = &(shm->data[bus].box[box].tgBox);
    mEnvData = &(shm->data[bus].box[box].env);
    updateData();
}

void BoxTotalWid::timeoutDone()
{
    updateData();
}
/*
void BoxTotalWid::setTemp(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = &(mEnvData->tem);

    double value = unit->value[id]/COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "°C";
    setTableItem(id, column, str);

    setAlarmStatus(id, column,unit->alarm[id], unit->crAlarm[id]);
}*/

void BoxTotalWid::updateData()
{
    QString str = QString::number(mTgBox->cur/COM_RATE_CUR, 'f', 1) + "A";
    ui->tCurLab->setText(str);

    str =  QString::number(mTgBox->pow/COM_RATE_POW, 'f', 3) + "kW";
    ui->tPowLab->setText(str);

    str =  QString::number(mTgBox->apPow/COM_RATE_POW, 'f', 3) + "kVA";
    ui->tApPowLab->setText(str);

    str =  QString::number(mTgBox->pf/COM_RATE_PF, 'f', 2);
    ui->tPfLab->setText(str);

    str =  QString::number(mTgBox->ele/COM_RATE_ELE, 'f', 1) + "kWh";
    ui->tEleLab->setText(str);

    str = QString::number(mTgBox->vol) + "V";
    ui->vollab->setText(str);


    sDataUnit *unit = &(mEnvData->tem);
    str =  QString::number(unit->value[0]) + "°C";
    setLabeColor(ui->tem1, unit->alarm[0], unit->crAlarm[0]);
    ui->tem1->setText(str);

    str =  QString::number(unit->value[1]) + "°C";
    setLabeColor(ui->tem2, unit->alarm[1], unit->crAlarm[1]);
    ui->tem2->setText(str);

    str =  QString::number(unit->value[2]) + "°C";
    setLabeColor(ui->tem3, unit->alarm[2], unit->crAlarm[2]);
    ui->tem3->setText(str);

}

void BoxTotalWid::setLabeColor(QLabel *label, int alarm, int crAlarm)
{
    QPalette pa;
    if(alarm) { // 报警
        pa.setColor(QPalette::WindowText,Qt::red);
    } else  if(crAlarm) { // 预警
        pa.setColor(QPalette::WindowText,Qt::yellow);
    } else {
        pa.setColor(QPalette::WindowText,Qt::black);
    }
    label->setPalette(pa);
}
