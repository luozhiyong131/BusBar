#include "systemsettingdlg.h"
#include "ui_systemsettingdlg.h"

SystemSettingDlg::SystemSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingDlg)
{
    ui->setupUi(this);
    mIpWid = new IpSettingDlg(ui->smtpWid);
}

SystemSettingDlg::~SystemSettingDlg()
{
    delete ui;
}



