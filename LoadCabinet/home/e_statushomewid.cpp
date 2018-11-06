#include "e_statushomewid.h"
#include "ui_e_statushomewid.h"
#include "in_com/in_datapackets.h"

E_statusHomeWid::E_statusHomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::E_statusHomeWid)
{
    ui->setupUi(this);

    mSec = 0;
    isRun = false;
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

E_statusHomeWid::~E_statusHomeWid()
{
    delete ui;
}

void E_statusHomeWid::updateWid()
{
    int mode = 1;
    IN_DataPackets *packets = IN_DataPackets::bulid();

    double value = packets->getTgValue(mode++) / COM_RATE_VOL;
    QString str = QString::number(value) + " V";
    ui->volLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_CUR;
    str = QString::number(value) + " A";
    ui->volLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_POW;
    str = QString::number(value) + " KW";
    ui->powLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_ELE;
    str = QString::number(value) + " KWh";
    ui->powLab->setText(str);

    value = packets->getTgValue(mode++);
    str = QString::number(value) + " HZ";
    ui->hzLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_TEM;
    str = QString::number(value) + " ℃";
    ui->temLab->setText(str);
}

bool E_statusHomeWid::checkRunTime()
{
    bool ret = ui->timeCheckBox->isChecked();
    if(!ret)
    {
        int sec = ui->timeSpinBox->value() * 60;
        if(sec > mSec) ret = true;
    }

    return ret;
}

void E_statusHomeWid::updateRunTime()
{
    QString str = "---";
    if(isRun) {
        bool ret = checkRunTime();
        if(ret) {
            int min = mSec++ / 60 ;
            int hour = min / 60;
            int day = hour / 24;
            str = tr("%1天 %2时 %3分 %4抄").arg(day).arg(hour%24).arg(min%60).arg(mSec%60);
        } else {
            on_startBtn_clicked();
        }
    }
    ui->timeLab->setText(str);
}

void E_statusHomeWid::timeoutDone()
{
    updateWid();
    updateRunTime();
}

void E_statusHomeWid::openInput()
{
    int start = ui->inputStartSpinBox->value();
    int end = ui->inputEndSpinBox->value();

    if(ui->inputCheckBox->isChecked()) {
        on_openBtn_clicked();
    } else {
        for(int i=start; i<=end; ++i) {
            int addr = i / 8 +1; int bit = i % 8;
            ELoad_RtuSent::bulid()->switchOpenCtr(addr, bit);
        }
    }
}

void E_statusHomeWid::setMode()
{
    int mode = ui->modeBox->currentIndex();
    switch(mode) {
    case 0: // 自动调整模块
        ELoad_RtuSent::bulid()->setAllDpAdjust();
        break;
    case 1: // 大电流模式

        break;

    case 2: // 手动模式

        break;
    }
}

void E_statusHomeWid::startUp()
{
    mSec = 0;
    isRun = true;

    openInput();
    setMode();
    ui->groupBox->setEnabled(false);
    ui->startBtn->setText(tr("停止"));
}

void E_statusHomeWid::stopFun()
{
    isRun = false;

    ui->groupBox->setEnabled(true);
    ui->startBtn->setText(tr("启动"));
}

void E_statusHomeWid::on_startBtn_clicked()
{
    on_closeBtn_clicked();
    if(isRun) {
        stopFun();
    } else {
        startUp();
    }
}

void E_statusHomeWid::on_openBtn_clicked()
{
    ELoad_RtuSent::bulid()->switchOpenAll();
}

void E_statusHomeWid::on_closeBtn_clicked()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
}
