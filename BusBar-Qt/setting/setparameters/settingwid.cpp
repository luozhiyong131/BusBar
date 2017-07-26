#include "settingwid.h"
#include "ui_settingwid.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    initWidget();

    ui->stackedWidget->setCurrentWidget(majorSettingWidget);
    majorSettingWidget->updateWidget(0);

}

SettingWid::~SettingWid()
{
    delete ui;
}



void SettingWid::initWidget()
{
    majorSettingWidget = new MajorSetting(ui->stackedWidget);
    ui->stackedWidget->addWidget(majorSettingWidget);

    mSubsettingWid = new SubSeeting(ui->stackedWidget);
    ui->stackedWidget->addWidget(mSubsettingWid);

    mSystemDlg = new SystemSettingDlg(ui->stackedWidget);
    ui->stackedWidget->addWidget(mSystemDlg);
}

/**
 * @brief 主路源发生变化，即母线切换
 * @param index
 */
void SettingWid::busChangedSlot(int index)
{
    majorSettingWidget->updateWidget(index);
    mSubsettingWid->updateWid(index);
}

/**
 * @brief 主路设置
 */
void SettingWid::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(majorSettingWidget);
}

/**
 * @brief 支路设置按钮
 */
void SettingWid::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(mSubsettingWid);
    mSubsettingWid->updateWid(0);
}

/**
 * @brief SettingWid::on_pushButton_3_clicked 系统设置
 */
void SettingWid::on_pushButton_3_clicked()
{   
    bool ret = false;
    CheckPasswordDlg checkDlg(NULL);

    if(QDialog::Accepted == checkDlg.exec())
    {
        qDebug() << "close";

        ret = checkDlg.getResult();

        qDebug() << "---ret---" << ret;
        if(ret)
            ui->stackedWidget->setCurrentWidget(mSystemDlg);
        else
            QMessageBox::information(this,"information","对不起，密码输入不正确，你不具备该权限！","确认");
    }
}
