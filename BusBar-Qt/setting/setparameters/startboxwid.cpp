#include "startboxwid.h"
#include "ui_startboxwid.h"

startBoxWid::startBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startBoxWid)
{
    ui->setupUi(this);
}

startBoxWid::~startBoxWid()
{
    delete ui;
}
