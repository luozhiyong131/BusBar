#include "systemsettingdlg.h"
#include "ui_systemsettingdlg.h"
#include <time.h>

SystemSettingDlg::SystemSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingDlg)
{
    ui->setupUi(this);
    mEmailWid = new EmailWid(ui->smtpWid);
    mNetWid = new NetSettingDlg(ui->netWid);
    mOtherWid = new OtherSettingDlg(ui->otherWid);
}

SystemSettingDlg::~SystemSettingDlg()
{
    delete ui;
}





//void SystemSettingDlg::on_pushButton_clicked()
//{
//    system("reboot");
//}
