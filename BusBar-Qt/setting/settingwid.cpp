﻿#include "settingwid.h"
#include "ui_settingwid.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    initWidget();

    ui->stackedWidget->setCurrentWidget(majorSettingWidget);


}

SettingWid::~SettingWid()
{
    delete ui;
}

/**
 * @brief 主路设置
 */
void SettingWid::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(majorSettingWidget);

    int index = ui->comboBox->currentIndex();
    majorSettingWidget->updateWidget(index);

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
void SettingWid::on_comboBox_currentIndexChanged(int index)
{
    majorSettingWidget->updateWidget(index);
    mSubsettingWid->updateWid(index);
}

/**
 * @brief 支路设置按钮
 */
void SettingWid::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(mSubsettingWid);
    int index = ui->comboBox->currentIndex();
    mSubsettingWid->updateWid(index);
}

void SettingWid::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(mSystemDlg);
}
