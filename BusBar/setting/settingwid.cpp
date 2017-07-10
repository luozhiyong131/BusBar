#include "settingwid.h"
#include "ui_settingwid.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    initWidget();

    //    int index = 0;
    //    majorSettingWidget->updateWidget(index);
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
}

/**
 * @brief 主路源发生变化，即母线切换
 * @param index
 */
void SettingWid::on_comboBox_currentIndexChanged(int index)
{
    majorSettingWidget->updateWidget(index);
}
