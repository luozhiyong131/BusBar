#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     test = new Serial_Test ;
}

MainWindow::~MainWindow()
{
    delete ui;
    share_mem_del();
}
