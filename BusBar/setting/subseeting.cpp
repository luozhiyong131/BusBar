#include "subseeting.h"
#include "ui_subseeting.h"

SubSeeting::SubSeeting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubSeeting)
{
    ui->setupUi(this);
}

SubSeeting::~SubSeeting()
{
    delete ui;
}
