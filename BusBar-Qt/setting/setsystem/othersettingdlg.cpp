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
    QuMsgBox box(this, tr("是否升级系统?"));
    if(box.Exec()) {
        QFileInfo fi("/mnt/sda1/busbar/app");                     // 目录存在
        if(fi.exists()) {
            int ret = system("rm -rf /mnt/mtdblock3/app");
            if(ret < 0) {
                qDebug() << "rm -rf /mnt/mtdblock3/app err ";
            }
            ret = system("mv /mnt/sda1/busbar/app /mnt/mtdblock3/app");
            if(ret < 0) {
                qDebug() << "mv /mnt/sda1/busbar/app /mnt/mtdblock3/app err ";
            }
             system("reboot");
        } else {
            CriticalMsgBox box(this, tr("升级文件未找到！\n 请插入U盘，把升级文件放入busbar目录下!"));
        }
    }

}

void OtherSettingDlg::on_resetBtn_clicked()
{
    QuMsgBox box(this, tr("是否重启系统?"));
    if(box.Exec()) {
        system("reboot");
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
