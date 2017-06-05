#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testdlg.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//     test = new Serial_Test ;

     TestDlg *dlg = new TestDlg(this);
     dlg->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
    share_mem_del();
}
