#include "thdmainwid.h"
#include "ui_thdmainwid.h"

ThdMainWid::ThdMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThdMainWid)
{
    ui->setupUi(this);

    mChartWid = new ThdChartWid(ui->chartwid);

    mTableWid = new ThdTableWid(ui->tablewid);
    QGridLayout *layout = new QGridLayout(ui->tablewid);
    layout->addWidget(mTableWid);
    layout->setSpacing(0);
    layout->setContentsMargins(5, 0, 5, 0);

    ushort buf[40];

    for(int i=0; i<40; ++i) {
        buf[i] = i*30;
    }
    mChartWid->updateData(buf, 30);
    mTableWid->updateData(buf, 30);
}

ThdMainWid::~ThdMainWid()
{
    delete ui;
}
