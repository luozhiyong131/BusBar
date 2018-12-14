#include "bus_mainwid.h"
#include "ui_bus_mainwid.h"
#include "bus_rtu/bus_rtuthread.h"
#include "bus_dp/bus_dpthread.h"
#include "bus_currentalarmsdlg.h"

extern int get_alarm_len();

BUS_MainWid::BUS_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_MainWid)
{
    ui->setupUi(this);

    mIndex = 0;
    initWidget();
    updateTime();

    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
    on_comboBox_currentIndexChanged(0);
}

BUS_MainWid::~BUS_MainWid()
{
    delete ui;
}


/**
 * @brief 初始化串口
 */
void BUS_MainWid::initSerial()
{
    ///============== 串口初始化需要 完善功能，，打开串口
    ///
    for(int i=0; i<BUS_NUM; ++i) {
        BUS_RtuThread *rtu = new BUS_RtuThread(this);
        rtu->init(i);
    }
}


void BUS_MainWid::updateTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->timeBtn->setText(time);
}

void BUS_MainWid::timeoutDone()
{
    updateTime();
    checkAlarm();
    setBusName(mIndex);

    for(int i=0; i<BUS_NUM; ++i)
        updateBusName(i);
}

QString BUS_MainWid::updateBusName(int index)
{
    sDataPacket *shm = BUS_DataPackets::bulid()->getBox(index, 0);
    QString str = QString("0%1 %2").arg(index+1).arg(shm->name);
    ui->comboBox->setItemText(index, str);
    ui->busNameLab->setText(str);

    return str;
}

void BUS_MainWid::setBusName(int index)
{
    mIndex = index;
    updateBusName(index);

    sDataPacket *shm = BUS_DataPackets::bulid()->getBox(index, 0);
    double rateCur = shm->ratedCur/COM_RATE_CUR;
    ui->ratedLab->setText(QString::number(rateCur));
    ui->ratedLab->setText("V2.0.0");
}

void BUS_MainWid::checkAlarm()
{
    int alarm = get_alarm_len();
    if(alarm)  {
        ui->alarmBtn->setVisible(true);
    } else {
        ui->alarmBtn->setVisible(false);
    }
}

void BUS_MainWid::initFunSLot()
{
    initSerial(); //串口
    new BUS_DpThread(this); // 创建数据处理线程
    updateTime();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

    mCheckDlg = new CheckPasswordDlg(this);
    connect(mCheckDlg,SIGNAL(dialogClosed(bool)),this,SLOT(dialogClosed(bool)));
}

void BUS_MainWid::initWidget()
{
    set_background_icon(ui->stackedWid,":/new/prefix1/image/background.png");
    initBackground(); //按钮图标

    mHomeWid = new BUS_HomeWid(ui->stackedWid); //主界面
    ui->stackedWid->addWidget(mHomeWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mHomeWid, SIGNAL(busChangedSig(int)));

    mLineWid = new BUS_LineWid(ui->stackedWid); //主路信息
    ui->stackedWid->addWidget(mLineWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLineWid, SIGNAL(busChangedSig(int)));

    mBranchWid = new BUS_BranchWid(ui->stackedWid); //支路信息
    ui->stackedWid->addWidget(mBranchWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mBranchWid, SIGNAL(busChangedSig(int)));

    mLogsWid = new BUS_LogsWid(ui->stackedWid); //日志
    ui->stackedWid->addWidget(mLogsWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLogsWid, SIGNAL(busChangedSig(int)));

    mSettingWid = new SetMainWid(ui->stackedWid); //配置
    ui->stackedWid->addWidget(mSettingWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mSettingWid, SLOT(busChangedSlot(int)));
}

void BUS_MainWid::on_homeBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mHomeWid);
    setButtonClickedImage(ui->homeBtn,"home_select");
}

void BUS_MainWid::on_lineBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLineWid);
    setButtonClickedImage(ui->lineBtn,"main_select");
}

void BUS_MainWid::on_branchBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBranchWid);
    setButtonClickedImage(ui->branchBtn,"branch_select");
}

void BUS_MainWid::on_logBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLogsWid);
    setButtonClickedImage(ui->logBtn,"data_select");
}

void BUS_MainWid::on_setBtn_clicked()
{
    if(ui->stackedWid->currentWidget() != mSettingWid) {
        mCheckDlg->exec();
    }
}

void BUS_MainWid::on_alarmBtn_clicked()
{
    BUS_CurrentAlarmsDlg dlg(this);
    dlg.exec();
}

void BUS_MainWid::on_comboBox_currentIndexChanged(int index)
{
    setBusName(index);
}

void BUS_MainWid::setButtonImage(QToolButton *button, QString name)
{
    QString str = tr("QToolButton{border-image: url(:/new/prefix1/image/%1.png);}").arg(name);
    button->setStyleSheet(str);
}

void BUS_MainWid::setButtonClickedImage(QToolButton *button, QString name)
{
    initBackground();
    QString str = tr("QToolButton{border-image: url(:/new/prefix1/image/%1.png);}").arg(name);
    button->setStyleSheet(str);
}

void BUS_MainWid::initBackground()
{
    setButtonImage(ui->homeBtn,"home");
    setButtonImage(ui->lineBtn,"main");
    setButtonImage(ui->branchBtn,"branch");
    setButtonImage(ui->logBtn,"data");
    setButtonImage(ui->setBtn,"setting");
}

void BUS_MainWid::dialogClosed(bool ret)
{
    if(ret)
    {
        ui->stackedWid->setCurrentWidget(mSettingWid);
        setButtonClickedImage(ui->setBtn,"setting_select");
    }
    else
        QMessageBox::information(this,"information","对不起，密码输入不正确，您不具备该权限！","确认");
    mCheckDlg->clear();
}

void BUS_MainWid::on_timeBtn_clicked()
{

}
