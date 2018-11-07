#include "e_inputunitwid.h"
#include "ui_e_inputunitwid.h"

E_InputUnitWid::E_InputUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::E_InputUnitWid)
{
    ui->setupUi(this);
    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
}

E_InputUnitWid::~E_InputUnitWid()
{
    delete ui;
}

void E_InputUnitWid::initFunSLot()
{
    rtu = ELoad_RtuSent::bulid();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void E_InputUnitWid::init(int addr, int bit)
{
    mObjData = &(IN_DataPackets::bulid()->getDev(addr)->data.input[bit]);
    QString str = QString::number(addr * 8 + bit+1);
    ui->inputLab->setText(str);
    mAddr = addr;
    mBit = bit;
}

void E_InputUnitWid::updateWid()
{
    if(mObjData->cur.value) {
        double value = mObjData->cur.value / COM_RATE_CUR;
        QString str = QString::number(value) + " A";
        ui->curLab->setText(str);

        QPalette pe;
        if(mObjData->cur.alarm) {
            pe.setColor(QPalette::WindowText,Qt::red);
        } else {
            pe.setColor(QPalette::WindowText,Qt::black);
        }
        ui->curLab->setPalette(pe);

        str = tr("断开");
        if(mObjData->sw == 1) {
            str = tr("接通");
            pe.setColor(QPalette::WindowText,Qt::black);
        } else {
            pe.setColor(QPalette::WindowText,Qt::red);
        }
        ui->swLab->setText(str);
        ui->swLab->setPalette(pe);
    }
}

void E_InputUnitWid::timeoutDone()
{
    updateWid();
}

void E_InputUnitWid::on_openBtn_clicked()
{
    rtu->switchOpenCtr(mAddr, mBit);
}

void E_InputUnitWid::on_closeBtn_clicked()
{
    rtu->switchCloseCtr(mAddr, mBit);
}

void E_InputUnitWid::on_checkBox_clicked(bool checked)
{
    ui->horizontalScrollBar->setEnabled(!checked);
    if(checked) {
        rtu->setDpAdjust(mAddr, ELoad_DP_1+mBit, 0 , 1000, 10);
    } else {
        rtu->setData(mAddr, ELoad_DP_1+mBit, 0);
    }
}

void E_InputUnitWid::on_horizontalScrollBar_valueChanged(int value)
{
    rtu->setData(mAddr, ELoad_DP_1+mBit, value);
}
