#include "logmainwid.h"
#include "ui_logmainwid.h"

LogMainWid::LogMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogMainWid)
{
    ui->setupUi(this);
}

LogMainWid::~LogMainWid()
{
    delete ui;
}
