#include "settingwid.h"
#include "ui_settingwid.h"
#include "interfacechangesig.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);

    isRun = false;
    mIndex = 0;
    QTimer::singleShot(10,this,SLOT(initFunSLot())); //延时初始化
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

void SettingWid::initFunSLot()
{
    initWidget();

    ui->stackedWidget->setCurrentWidget(majorSettingWidget);
    majorSettingWidget->updateWidget(0);
    mSubsettingWid->updateWid(0);
    mTemWid->updateWid(0);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateWid()));
    timer->start(5*1000);

    connect(this,SIGNAL(indexChanged(int)),majorSettingWidget,SLOT(indexChanged(int)));
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));
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

    emit indexChanged(index);
}

void SettingWid::updateWid()
{
    if(isRun) {
        int index = mIndex;
        majorSettingWidget->updateWidget(index);
        mSubsettingWid->updateWid(index);
        mTemWid->updateWid(index);
    }
}


void SettingWid::interfaceChangedSlot(int id)
{
    if(id == 5) {
        isRun = true;
    } else {
        isRun = false;
    }
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
