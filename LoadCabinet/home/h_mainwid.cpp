#include "h_mainwid.h"
#include "ui_h_mainwid.h"

H_MainWid::H_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H_MainWid)
{
    ui->setupUi(this);

    mInputWid = new E_InputHomeWid(ui->widget_1);
    mStatusWid = new E_statusHomeWid(ui->widget_2);
}

H_MainWid::~H_MainWid()
{
    delete ui;
}
