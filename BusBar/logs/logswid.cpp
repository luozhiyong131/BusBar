#include "logswid.h"
#include "ui_logswid.h"

LogsWid::LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogsWid)
{
    ui->setupUi(this);
}

LogsWid::~LogsWid()
{
    delete ui;
}
