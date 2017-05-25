#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datapacket.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sDataPacket *mem = share_mem_get();
//    mem->data[0].busAlarm = '5';
    qDebug() << mem->data[0].busAlarm;
//        share_mem_init();


         qDebug() << mem->data[0].boxNum;


        share_mem_del();
}

MainWindow::~MainWindow()
{
    delete ui;
}
