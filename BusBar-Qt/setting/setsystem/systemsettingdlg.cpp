#include "systemsettingdlg.h"
#include "ui_systemsettingdlg.h"
#include <time.h>

SystemSettingDlg::SystemSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingDlg)
{
    ui->setupUi(this);
    mEmailWid = new EmailWid(ui->smtpWid);
}

SystemSettingDlg::~SystemSettingDlg()
{
    delete ui;
}

/**
 * @brief 时间设置保存
 */
void SystemSettingDlg::on_pushButton_7_clicked()
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
    if(ret = -1)
        qDebug() << "time setting error";
    else
        qDebug() << "time setting success";
}
