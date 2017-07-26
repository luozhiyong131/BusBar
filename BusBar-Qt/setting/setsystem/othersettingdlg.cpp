#include "othersettingdlg.h"
#include "ui_othersettingdlg.h"

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

/**
 * @brief OtherSettingDlg::on_pushButton_3_clicked 密码
 */
void OtherSettingDlg::on_pushButton_3_clicked()
{
    PassordSettingDlg *passwordDlg = new PassordSettingDlg(this);
    passwordDlg->exec();
}

/**
 * @brief OtherSettingDlg::on_pushButton_clicked  时间
 */
void OtherSettingDlg::on_pushButton_clicked()
{
    DatetimeSettingDlg *datetimeDlg = new DatetimeSettingDlg(this);
    datetimeDlg->exec();
}

/**
 * @brief OtherSettingDlg::on_pushButton_2_clicked 重启
 */
void OtherSettingDlg::on_pushButton_2_clicked()
{
    switch (QMessageBox::information(this,"waring","是否重启系统","确定","取消",0,1)) {
    case 0:
        system("reboot");
        break;
    case 1:

        break;
    default:
        break;
    }

}
