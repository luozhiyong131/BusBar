/*
 * 主界面程序
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datetime/timesettingdlg.h"
#include "netdataanalyze.h"
#include "dpthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    com_setBackColour("Home", this);

    QFontDatabase database;
    foreach (const QString &family, database.families(QFontDatabase::SimplifiedChinese))
    {
        qDebug()<<family;
    }

    mShow = 1;
    ui->widget->setStyleSheet("background-color:#0064CD;");
    ui->logoLab->setPixmap(QPixmap(":/image/logo.png").scaled(ui->logoLab->size()));
    ui->label->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->timeBtn->setStyleSheet("QToolButton{""border-radius:5px}"); //边框角的弧度为8px
    ui->homeBtn->setStyleSheet("QToolButton{""border-radius:5px}" );
    ui->logsBtn ->setStyleSheet( "QToolButton{""border-radius:5px}" );
    ui->setBtn->setStyleSheet( "QToolButton{""border-radius:5px}" );
    //"QToolButton:hover{background-color:rgb(91, 237, 238);}"
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

void MainWindow::onCShow(int value) //切换图标
{
    switch (mShow){
    case 1 :  ui->homeBtn->setIcon(QIcon(":/image/home.png")); break;
    case 2 :  ui->logsBtn->setIcon(QIcon(":/image/data.png")); break;
    case 3 :  ui->setBtn->setIcon(QIcon(":/image/setting.png")); break;
    //default : 语句n break;
    }
    mShow = value;
    switch (mShow){
    case 1 :  ui->homeBtn->setIcon(QIcon(":/image/home_select.png")); break;
    case 2 :  ui->logsBtn->setIcon(QIcon(":/image/data_select.png")); break;
    case 3 :  ui->setBtn->setIcon(QIcon(":/image/setting_select.png")); break;
    //default : 语句n break;
    }
}

void MainWindow::initFunSLot()
{
    updateTime();
    initWidget();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

    new NetDataAnalyze(this);
    new DpThread(this);
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
    onCShow(1);
}

void MainWindow::on_logsBtn_clicked()
{
     ui->stackedWid->setCurrentWidget(mLogWid);
     onCShow(2);
}

void MainWindow::on_setBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mSetWid);
    onCShow(3);
}
