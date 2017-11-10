#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "netdataanalyze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NetDataAnalyze *net = new NetDataAnalyze(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
