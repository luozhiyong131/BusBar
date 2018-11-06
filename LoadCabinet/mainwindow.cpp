/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timesettingdlg.h"
#include "beepthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->titleWid->setStyleSheet("background-color:#0064CD;");

    set_background_icon(ui->titleWid,":/image/title_back.jpg");


    QTimer::singleShot(10,this,SLOT(initFunSLot())); //延时初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    mInputWid = new IN_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputWid);

}


void MainWindow::initFunSLot()
{
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    BeepThread::bulid()->longBeep();

    initWidget();
}



void MainWindow::timeoutDone()
{
    updateTime();
}



void MainWindow::updateTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd  hh:mm:ss");
    ui->timeBtn->setText(time);
}

void MainWindow::on_timeBtn_clicked()
{
    TimeSettingDlg dlg(this);
    dlg.exec();
}

void MainWindow::on_homeBtn_clicked()
{

}

void MainWindow::on_inputBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mInputWid);
}
