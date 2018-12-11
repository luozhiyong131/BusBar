#include "bus_branchwid.h"
#include "ui_bus_branchwid.h"

BUS_BranchWid::BUS_BranchWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_BranchWid)
{
    ui->setupUi(this);
    mTableWid = new BUS_BranchTableWid(ui->widget);
    connect(this, SIGNAL(busChangedSig(int)), mTableWid, SLOT(busChangeSlot(int)));
}


BUS_BranchWid::~BUS_BranchWid()
{
    delete ui;
}
