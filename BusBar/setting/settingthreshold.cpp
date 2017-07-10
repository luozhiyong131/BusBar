#include "settingthreshold.h"
#include "ui_settingthreshold.h"

SettingThreshold::SettingThreshold(sObjData *data,bool isCur,int index ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingThreshold)
{
    ui->setupUi(this);

    mData = data;
    mIsCur = isCur;
    mIndex = index;
}

SettingThreshold::~SettingThreshold()
{
    delete ui;
}

void SettingThreshold::on_pushButton_clicked()
{
    this->close();
}
