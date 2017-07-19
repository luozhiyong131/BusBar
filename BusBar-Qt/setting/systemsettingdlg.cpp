#include "systemsettingdlg.h"
#include "ui_systemsettingdlg.h"
#include <time.h>

SystemSettingDlg::SystemSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingDlg)
{
    ui->setupUi(this);
}

SystemSettingDlg::~SystemSettingDlg()
{
    delete ui;
}

void SystemSettingDlg::setDate(QString year, QString month, QString day, QString hour, QString minute, QString second)
{
       QString str= "date -s " + year + month + day + hour + minute ;
    //    QString str = "date -s " + "20090807 16:02:23";
    system(str.toLatin1().data());
    //强制写入到CMOS
    system("hwclock -w");
    //    system("clock -w");
}

/**
 * @brief 时间设置保存
 */
void SystemSettingDlg::on_pushButton_7_clicked()
{

#if 0
    struct tm nowtime;

    time_t t;

    nowtime.tm_sec=56;/* Seconds.[0-60](1 leap second)*/

    nowtime.tm_min=34;/* Minutes.[0-59] */

    nowtime.tm_hour=12;/* Hours. [0-23] */

    nowtime.tm_mday=23;/*  Day.[1-31]  */

    nowtime.tm_mon=8;/* Month.[0-11]*/

    nowtime.tm_year=2013;/* Year- 1900.*/

    nowtime.tm_isdst=-1;/*DST.[-1/0/1]*/

    t=mktime(&nowtime);

    stime(&t);

#else
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    QString year =QString::number( dateTime.date().year(),10);
    QString month = QString::number( dateTime.date().month());
    QString day = QString::number( dateTime.date().day());
    QString hour = QString::number(dateTime.time().hour(),10);
    QString minute = QString::number(dateTime.time().minute(),10);
    QString second = QString::number(dateTime.time().second(),10);

    qDebug() << year << month << day << hour << minute << second ;

    setDate(year, month,  day,  hour,  minute,  second);
#endif

}
