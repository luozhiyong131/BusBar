#include "datetimesettingdlg.h"
#include "ui_datetimesettingdlg.h"

DatetimeSettingDlg::DatetimeSettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatetimeSettingDlg)
{
    ui->setupUi(this);
    initDateTime();
}

DatetimeSettingDlg::~DatetimeSettingDlg()
{
    delete ui;
}

void DatetimeSettingDlg::on_pushButton_7_clicked()
{
    QDateTime datetime = ui->dateTimeEdit->dateTime();
    settingTime time;

    time.sec = 0;
    time.min = datetime.time().minute();
    time.hour= datetime.time().hour();
    time.day = datetime.date().day();
    time.mon  = datetime.date().month();
    time.year = datetime.date().year();

    int ret = SetSystemTime(&time);
//    if(ret = -1)
//        qDebug() << "time setting error";
//    else
//        qDebug() << "time setting success";

    this->close();
}

void DatetimeSettingDlg::initDateTime()
{
    ui->dateTimeEdit->setEnabled(false);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

void DatetimeSettingDlg::on_comboBox_currentIndexChanged(int index)
{
    if(index)
        ui->dateTimeEdit->setEnabled(true);
    else
        ui->dateTimeEdit->setEnabled(false);
}
