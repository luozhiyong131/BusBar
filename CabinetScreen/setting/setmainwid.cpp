#include "setmainwid.h"
#include "ui_setmainwid.h"

SetMainWid::SetMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetMainWid)
{
    ui->setupUi(this);
}

SetMainWid::~SetMainWid()
{
    delete ui;
}
