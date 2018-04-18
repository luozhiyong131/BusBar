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

    ui->label->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->logoBtn->setStyleSheet("QToolButton{""border-radius:5px}"); //边框角的弧度为8px
    ui->logoBtn->setIconSize(ui->logoBtn->size());
    ui->logoBtn->setIcon(QPixmap(":/image/logo.png").scaled(ui->logoBtn->size()));
    connect(ui->logoBtn, SIGNAL(longPressSig(int)), this, SLOT(onLongPressSlot(int)));

    ui->timeBtn->setStyleSheet("QToolButton{""border-radius:5px}"); //边框角的弧度为8px
    ui->homeBtn->setStyleSheet("QToolButton{""border-radius:5px}" );
    ui->logsBtn ->setStyleSheet( "QToolButton{""border-radius:5px}" );
    ui->setBtn->setStyleSheet( "QToolButton{""border-radius:5px}" );

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

static bool update_fun(const QString &str)
{
    bool ret = true;

    QFileInfo fi(QString("/mnt/%1/CabinetScreen/app").arg(str));
    if(fi.exists()) {
        QString cstr;
        cstr = QString("rm -rf opt/app");
        int ret = system(cstr.toLatin1());
        if(ret < 0) {
            qDebug() << cstr.toLatin1() << " err ";
        }
        cstr = QString("cp /mnt/%1/CabinetScreen/app /opt/app").arg(str);
        ret = system(cstr.toLatin1());
        if(ret < 0) {
            qDebug() << cstr.toLatin1() << " err ";
        }
        system("reboot");
    } else {
        ret = false;
    }

    return ret;
}

void MainWindow::onLongPressSlot(int time)
{
    if(time < 3000) return;
    QuMsgBox box(this, tr("是否升级系统?"));
    if(box.Exec()) {
        bool ret = update_fun("udisk");
       // if(!ret) ret = update_fun("mmcblk0p1");
        if(!ret)
            CriticalMsgBox box(this, tr("升级文件未找到！\n 请插入U盘，把升级文件放入CabinetScreen目录下!"));
    }
}


