#include "thresholdunitwid.h"
#include "ui_thresholdunitwid.h"
#include "inputdlg.h"

ThresholdUnitWid::ThresholdUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThresholdUnitWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

ThresholdUnitWid::~ThresholdUnitWid()
{
    delete ui;
}



/**
 * @brief 初始化数据
 * @param id 设备号
 * @param mode 模式  1 电压  2 电流  3 温度 4 湿度
 * @param line 相数
 */
void ThresholdUnitWid::init(int id, int mode, int line)
{
    sDataPacket *packet = get_dev_dataPacket();
    sDevData *dev = &(packet->dev[id]);
    switch (mode) {
    case VolMode:
        mDataUnit = &(dev->data.vol);
        mStr = "V";
        mRate = COM_RATE_VOL;
        break;
    case CurMode:
        mDataUnit = &(dev->data.cur);
        mStr = "A";
        mRate = COM_RATE_CUR;
        break;
    case TemMode:
        mDataUnit = &(dev->env.tem);
        mStr = "℃";
        mRate = COM_RATE_TEM;
        break;
    case HumMode:
        mDataUnit = &(dev->env.hum);
        mStr = "%";
        mRate = COM_RATE_HUM;
        break;
    default:
        qDebug() << "ThresholdUnitWid init Err" << mode;
        break;
    }
    mDevId = id;
    mMode =mode;
    mLine = line;
    mDev = dev;
}

void ThresholdUnitWid::initWid()
{
    QString str = "---";

    ui->valueLab->setText(str);
    ui->minLab->setText(str);
    ui->maxLab->setText(str);
}


void ThresholdUnitWid::checkAlarm()
{
    QString str;
    int line = mLine;
    int alarm = mDataUnit->alarm[line];
    if(alarm) {
        str = "color: rgb(255, 0, 0);";
    } else {
        str = "color:black;";
    }

    ui->valueLab->setStyleSheet(str);
}

void ThresholdUnitWid::updateDataUnit()
{
    QString str;
    int line = mLine;

    double value = mDataUnit->value[line] / mRate;
    str = QString::number(value) + mStr;
    ui->valueLab->setText(str);

    value = mDataUnit->min[line] / mRate;
    str = QString::number(value) + mStr;
    ui->minLab->setText(str);

    value = mDataUnit->max[line] / mRate;
    str = QString::number(value) + mStr;
    ui->maxLab->setText(str);
}


void ThresholdUnitWid::timeoutDone()
{
    bool ret = true;
    if(mDev->offLine > 0) {
        updateDataUnit();
        checkAlarm();
    } else {
        initWid();
        ret = false;
    }
    ui->setBtn->setEnabled(ret);
}

void ThresholdUnitWid::on_setBtn_clicked()
{
    InputDlg dlg(this);
    dlg.init(mDevId, mMode, mLine);
    dlg.exec();
}
