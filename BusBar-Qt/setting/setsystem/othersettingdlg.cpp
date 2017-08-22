#include "othersettingdlg.h"
#include "ui_othersettingdlg.h"
#include "common.h"
#include "datetime/timesettingdlg.h"

OtherSettingDlg::OtherSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtherSettingDlg)
{
    ui->setupUi(this);
}

OtherSettingDlg::~OtherSettingDlg()
{
    delete ui;
}


void OtherSettingDlg::on_updateBtn_clicked()
{
    ///// ========== 从U盘把文件复制出来

}

void OtherSettingDlg::on_resetBtn_clicked()
{
    int ret = QMessageBox::information(this,"waring","是否重启系统","确定","取消",0,1);
    switch (ret) {
    case 0:
        system("reboot");
        break;
    case 1:

        break;
    default:
        break;
    }
}

void OtherSettingDlg::on_timeSetBtn_clicked()
{
    BeepThread::bulid()->beep();
    TimeSettingDlg dlg(this);
    dlg.exec();
}

void OtherSettingDlg::on_pwdSetBtn_clicked()
{
    PassordSettingDlg *passwordDlg = new PassordSettingDlg(this);
    passwordDlg->show();
}
