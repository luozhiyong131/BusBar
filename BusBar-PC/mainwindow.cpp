#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mBusWid = new BUS_MainWid(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
