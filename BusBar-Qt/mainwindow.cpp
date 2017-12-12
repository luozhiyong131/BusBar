#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rtuthread.h"
#include "dpthread.h"
#include "currentalarmsdlg.h"
#include "interfacechangesig.h"
#include "beepthread.h"
#include "datetime/timesettingdlg.h"
#include "net/send/netsendthread.h"

#include "shm/setbox.h"

RtuThread *rtu[4];
//extern RtuThread *rtu[4];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mInitShm = new InitShm(this); //线程
    mInitShm->start(); //初始化共享内存 -- 单线程运行一次

    initSerial(); //串口

    mIndex = 0;
    initWidget();
    updateTime();

    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
    on_comboBox_currentIndexChanged(0);
    BeepThread::bulid()->longBeep(); // 线程 -- 'bi~'

    //修改数据线程
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), SetBOXThread::bulid(), SLOT(busChangedSlot(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    share_mem_del();
}

/**
 * @brief 初始化串口
 */
void MainWindow::initSerial()
{
   rtu[0] = new RtuThread(this);
   rtu[0]->init(SERIAL_COM1, 1); //只操作母线1
#if BUS_NUM > 1
   rtu[1] = new RtuThread(this);
   rtu[1]->init(SERIAL_COM2, 2);
#endif
#if BUS_NUM > 2
   rtu[2] = new RtuThread(this);
   rtu[2]->init(SERIAL_COM3, 3);
#endif
#if BUS_NUM > 3
   rtu[3] = new RtuThread(this);
   rtu[3]->init(SERIAL_COM4, 4);
#endif
}

void MainWindow::updateTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->timeBtn->setText(time);
}

void MainWindow::timeoutDone()
{   
    updateTime();
    checkAlarm();
    setBusName(mIndex);
}

void MainWindow::setBusName(int index)
{
    sDataPacket *shm = get_share_mem();
    char *name = shm->data[index].busName;

    QString str(name);
    ui->busNameLab->setText(str);
    mIndex = index;

    sBusData *busData = &(shm->data[index]);
    double rateCur = busData->box[0].ratedCur/COM_RATE_CUR;
    ui->ratedLab->setText(QString::number(rateCur));
}

void MainWindow::checkAlarm()
{
    int alarm = 0;
    sDataPacket *shm = get_share_mem();
    for(int i=0; i>BUS_NUM; ++i) {
        alarm += shm->data[i].box[0].boxAlarm;
    }

    alarm = 1;  /////========= 特意显示出来
    if(alarm)  {
        ui->alarmBtn->setVisible(true);
    } else {
        ui->alarmBtn->setVisible(false);
    }
}

void MainWindow::initFunSLot()
{
    new DpThread(this); // 创建数据处理线程
    updateTime();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

    mCheckDlg = new CheckPasswordDlg(this);
    connect(mCheckDlg,SIGNAL(dialogClosed(bool)),this,SLOT(dialogClosed(bool)));

    mNetWork = new NetWork(this);
}

void MainWindow::initWidget()
{
    //    set_background_color(ui->stackedWid,Qt::white);
    set_background_icon(ui->stackedWid,":/new/prefix1/image/background.png");
    initBackground(); //按钮图标

    mHomeWid = new HomeWid(ui->stackedWid); //主界面
    ui->stackedWid->addWidget(mHomeWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mHomeWid, SIGNAL(busChangedSig(int)));

    mLineWid = new LineWid(ui->stackedWid); //主路信息
    ui->stackedWid->addWidget(mLineWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLineWid, SIGNAL(busChangedSig(int)));

    mBranchWid = new BranchWid(ui->stackedWid); //支路信息
    ui->stackedWid->addWidget(mBranchWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mBranchWid, SIGNAL(busChangedSig(int)));

    mLogsWid = new LogsWid(ui->stackedWid); //日志
    ui->stackedWid->addWidget(mLogsWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLogsWid, SIGNAL(busChangedSig(int)));

    mSettingWid = new SettingWid(ui->stackedWid); //配置
    ui->stackedWid->addWidget(mSettingWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mSettingWid, SLOT(busChangedSlot(int)));
}

void MainWindow::on_homeBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mHomeWid);
    setButtonClickedImage(ui->homeBtn,"home_select");

    InterfaceChangeSig::get()->changeType(1);
}

void MainWindow::on_lineBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLineWid);
    setButtonClickedImage(ui->lineBtn,"main_select");

    InterfaceChangeSig::get()->changeType(2);
}

void MainWindow::on_branchBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBranchWid);
    setButtonClickedImage(ui->branchBtn,"branch_select");

    InterfaceChangeSig::get()->changeType(3);
}

void MainWindow::on_logBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLogsWid);
    setButtonClickedImage(ui->logBtn,"data_select");
    InterfaceChangeSig::get()->changeType(4);
}

void MainWindow::on_setBtn_clicked()
{
    if(ui->stackedWid->currentWidget() != mSettingWid) {
        BeepThread::bulid()->beep();
        mCheckDlg->exec();
    }
}

void MainWindow::on_alarmBtn_clicked()
{
    BeepThread::bulid()->beep();
    CurrentAlarmsDlg dlg(this);
    dlg.exec();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    setBusName(index);
}

void MainWindow::setButtonImage(QToolButton *button, QString name)
{    
    QString str = tr("QToolButton{border-image: url(:/new/prefix1/image/%1.png);}").arg(name);
    button->setStyleSheet(str);
}

void MainWindow::setButtonClickedImage(QToolButton *button, QString name)
{
    initBackground();
    QString str = tr("QToolButton{border-image: url(:/new/prefix1/image/%1.png);}").arg(name);
    button->setStyleSheet(str);
}

void MainWindow::initBackground()
{
    setButtonImage(ui->homeBtn,"home");
    setButtonImage(ui->lineBtn,"main");
    setButtonImage(ui->branchBtn,"branch");
    setButtonImage(ui->logBtn,"data");
    setButtonImage(ui->setBtn,"setting");
}

void MainWindow::dialogClosed(bool ret)
{
    if(ret)
    {
        ui->stackedWid->setCurrentWidget(mSettingWid);
        setButtonClickedImage(ui->setBtn,"setting_select");
        InterfaceChangeSig::get()->changeType(5);
    }
    else
        QMessageBox::information(this,"information","对不起，密码输入不正确，您不具备该权限！","确认");
    mCheckDlg->clear();
}

void MainWindow::on_timeBtn_clicked()
{
    BeepThread::bulid()->beep();
    TimeSettingDlg dlg(this);
    dlg.exec();
}
