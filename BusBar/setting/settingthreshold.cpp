#include "settingthreshold.h"
#include "ui_settingthreshold.h"

SettingThreshold::SettingThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingThreshold)
{
    ui->setupUi(this);
}

SettingThreshold::~SettingThreshold()
{
    delete ui;
}
