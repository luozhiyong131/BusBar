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

static bool update_fun(const QString &str)
{
    bool ret = true;

    QFileInfo fi(QString("/mnt/%1/busbar/app").arg(str));
    if(fi.exists()) {
        int ret = system("rm -rf /mnt/mtdblock3/app");
        if(ret < 0) {
            qDebug() << "rm -rf /mnt/mtdblock3/app err ";
        }
        QString str = QString("mv /mnt/%1/busbar/app /mnt/mtdblock3/app").arg(str);
        ret = system(str.toLatin1());
        if(ret < 0) {
            qDebug() << str.toLatin1() << " err ";
        }
        system("reboot");
    } else {
        ret = false;
    }

    return ret;
}

void OtherSettingDlg::on_updateBtn_clicked()
{
    QuMsgBox box(this, tr("是否升级系统?"));
    if(box.Exec()) {

        bool ret = update_fun("sda1");
        if(!ret)
            ret = update_fun("mmcblk0p1");
        if(!ret)
            CriticalMsgBox box(this, tr("升级文件未找到！\n 请插入U盘，把升级文件放入busbar目录下!"));
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
