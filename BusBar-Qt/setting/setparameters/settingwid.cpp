#include "settingwid.h"
#include "ui_settingwid.h"
#include "interfacechangesig.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    this->setStyleSheet(BTN_FOCUS_BACK_COLOR);

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
    majorSettingWidget = new MajorSetting(ui->stackedWidget); //主路
    ui->stackedWidget->addWidget(majorSettingWidget);

    mSubsettingWid = new SubSeeting(ui->stackedWidget); //支路
    ui->stackedWidget->addWidget(mSubsettingWid);

    mTemWid = new TemSettingWid(ui->stackedWidget); //温度
    ui->stackedWidget->addWidget(mTemWid);

    mSystemDlg = new SystemSettingDlg(ui->stackedWidget); //系统
    ui->stackedWidget->addWidget(mSystemDlg);

    mSetNamesWid = new SetNamesWid(ui->stackedWidget); //名称
    ui->stackedWidget->addWidget(mSetNamesWid);

    setButtonColor(ui->pushButton);
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
    timer->start(2*1000);
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));

    ui->pushButton->setChecked(true);
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
    mSetNamesWid->indexChanged(index);
}

void SettingWid::updateWid()
{
    if(isRun) {
        int index = mIndex;
        majorSettingWidget->updateWidget(index);
        mSubsettingWid->updateWid(index);
        mTemWid->updateWid(index);
        mSetNamesWid->updateWid(index);
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

void SettingWid::setButtonColor(QPushButton *button)
{
    ui->pushButton->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_3->setStyleSheet("");
    ui->pushButton_tem->setStyleSheet("");
    ui->nameBtn->setStyleSheet("");

    button->setStyleSheet("background-color: rgb(96,238,250);");
}

/**
 * @brief 主路设置
 */
void SettingWid::on_pushButton_clicked()
{
    setButtonColor(ui->pushButton);
    ui->stackedWidget->setCurrentWidget(majorSettingWidget);
    BeepThread::bulid()->beep();
}

/**
 * @brief 支路设置按钮
 */
void SettingWid::on_pushButton_2_clicked()
{
    setButtonColor(ui->pushButton_2);
    ui->stackedWidget->setCurrentWidget(mSubsettingWid);
    BeepThread::bulid()->beep();
}

/**
 * @brief SettingWid::on_pushButton_3_clicked 系统设置
 */
void SettingWid::on_pushButton_3_clicked()
{   
    setButtonColor(ui->pushButton_3);
    ui->stackedWidget->setCurrentWidget(mSystemDlg);
    BeepThread::bulid()->beep();
}

/**
 * @brief SettingWid::on_pushButton_tem_clicked  温度阈值设置
 */
void SettingWid::on_pushButton_tem_clicked()
{
    setButtonColor(ui->pushButton_tem);
    ui->stackedWidget->setCurrentWidget(mTemWid);
    BeepThread::bulid()->beep();
}

void SettingWid::on_nameBtn_clicked()
{
    setButtonColor(ui->nameBtn);
    ui->stackedWidget->setCurrentWidget(mSetNamesWid);
    BeepThread::bulid()->beep();
}
