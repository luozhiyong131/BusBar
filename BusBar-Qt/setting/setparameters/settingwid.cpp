#include "settingwid.h"
#include "ui_settingwid.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    initWidget();

    mIndex = 0;

    ui->stackedWidget->setCurrentWidget(majorSettingWidget);
    majorSettingWidget->updateWidget(0);
    mSubsettingWid->updateWid(0);
    mTemWid->updateWid(0);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateWid()));
    timer->start(5*1000);
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

    mTemWid = new TemSettingWid(ui->stackedWidget);
    ui->stackedWidget->addWidget(mTemWid);

    mSystemDlg = new SystemSettingDlg(ui->stackedWidget);
    ui->stackedWidget->addWidget(mSystemDlg);
}

/**
 * @brief 主路源发生变化，即母线切换
 * @param index
 */
void SettingWid::busChangedSlot(int index)
{
    mIndex = index;
    majorSettingWidget->updateWidget(index);
    mSubsettingWid->updateWid(index);
    mTemWid->updateWid(index);
}

void SettingWid::updateWid()
{
    int index = mIndex;
    majorSettingWidget->updateWidget(index);
    mSubsettingWid->updateWid(index);
    mTemWid->updateWid(index);
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
}

/**
 * @brief SettingWid::on_pushButton_3_clicked 系统设置
 */
void SettingWid::on_pushButton_3_clicked()
{   
    ui->stackedWidget->setCurrentWidget(mSystemDlg);
}

/**
 * @brief SettingWid::on_pushButton_tem_clicked  温度阈值设置
 */
void SettingWid::on_pushButton_tem_clicked()
{
    ui->stackedWidget->setCurrentWidget(mTemWid);
}
