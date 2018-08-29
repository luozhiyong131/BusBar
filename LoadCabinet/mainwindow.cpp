/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataRecvWS = new WebSocket();
    qDebug()<<"create websocket!";
}

MainWindow::~MainWindow()
{
    delete ui;
}
