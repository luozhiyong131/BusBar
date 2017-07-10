#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rtuthread.h"
#include "dpthread.h"
#include "currentalarmsdlg.h"

#include "testdlg.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mInitShm = new InitShm(this);
    mInitShm->start();

//    initSerial();

    initWidget();
    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化

//     TestDlg *dlg = new TestDlg(this);
//     dlg->exec();
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

    mLineWid = new LineWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLineWid);

    mBranchWid = new BranchWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBranchWid);

    mLogsWid = new LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);

    mSettingWid = new SettingWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSettingWid);
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
