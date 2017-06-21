#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rtuthread.h"
#include "dpthread.h"

#include "testdlg.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mInitShm = new InitShm(this);

//    initSerial();
    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化

//     TestDlg *dlg = new TestDlg(this);
//     dlg->exec();
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
}
