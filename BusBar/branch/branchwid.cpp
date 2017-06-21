#include "branchwid.h"
#include "ui_branchwid.h"

BranchWid::BranchWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BranchWid)
{
    ui->setupUi(this);
}

BranchWid::~BranchWid()
{
    delete ui;
}
