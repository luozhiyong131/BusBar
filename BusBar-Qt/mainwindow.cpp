#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rtuthread.h"
#include "dpthread.h"
#include "currentalarmsdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mInitShm = new InitShm(this);
    mInitShm->start();

    // initSerial();

    initWidget();
    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
    on_comboBox_currentIndexChanged(0);
    // TestDlg *dlg = new TestDlg(this);
    // dlg->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
    share_mem_del();
}

void MainWindow::timeoutDone()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->timeLab->setText(time);
}

/**
 * @brief 初始化串口
 */
void MainWindow::initSerial()
{
    RtuThread *rtu = new RtuThread(this);
    rtu->init(SERIAL_COM1, 1);

    rtu = new RtuThread(this);
    rtu->init(SERIAL_COM2, 2);

    rtu = new RtuThread(this);
    rtu->init(SERIAL_COM3, 3);

    rtu = new RtuThread(this);
    rtu->init(SERIAL_COM4, 4);
}


void MainWindow::initFunSLot()
{
    new DpThread(this); // 创建数据处理线程

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void MainWindow::initWidget()
{
    mHomeWid = new HomeWid(ui->stackedWid);
    ui->stackedWid->addWidget(mHomeWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mHomeWid, SIGNAL(busChangedSig(int)));

    mLineWid = new LineWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLineWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLineWid, SIGNAL(busChangedSig(int)));

    mBranchWid = new BranchWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBranchWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mBranchWid, SIGNAL(busChangedSig(int)));

    mLogsWid = new LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mLogsWid, SIGNAL(busChangedSig(int)));

    mSettingWid = new SettingWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSettingWid);
     connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mSettingWid, SLOT(busChangedSlot(int)));
}

void MainWindow::on_homeBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mHomeWid);
}

void MainWindow::on_lineBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLineWid);
}

void MainWindow::on_branchBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBranchWid);
}

void MainWindow::on_logBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mLogsWid);
}

void MainWindow::on_setBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mSettingWid);
}

void MainWindow::on_alarmBtn_clicked()
{
    CurrentAlarmsDlg dlg(this);
    dlg.exec();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
     sDataPacket *shm = get_share_mem();
     char *name = shm->data[index].busName;

     QString str(name);
     ui->busNameLab->setText(str);
}
