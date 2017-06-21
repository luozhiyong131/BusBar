#include "linewid.h"
#include "ui_linewid.h"

LineWid::LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWid)
{
    ui->setupUi(this);
}

LineWid::~LineWid()
{
    delete ui;
}
