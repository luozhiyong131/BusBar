/*
 * 主界面程序
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datetime/timesettingdlg.h"
#include "netdataanalyze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    com_setBackColour("Home", this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    mHomeWid = new HomeMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mHomeWid);

    mLogWid = new LogMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogWid);

    mSetWid = new SetMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetWid);
}

void MainWindow::initFunSLot()
{
    new NetDataAnalyze(this);
    updateTime();
    initWidget();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


void MainWindow::updateTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd  hh:mm:ss");
    ui->timeBtn->setText(time);
}

void MainWindow::timeoutDone()
{
    updateTime();
}

void MainWindow::on_timeBtn_clicked()
{
    TimeSettingDlg dlg(this);
    dlg.exec();
}

void MainWindow::on_homeBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mHomeWid);
}

void MainWindow::on_logsBtn_clicked()
{
     ui->stackedWid->setCurrentWidget(mLogWid);
}

void MainWindow::on_setBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mSetWid);
}
