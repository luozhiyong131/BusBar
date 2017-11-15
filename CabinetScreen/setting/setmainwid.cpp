#include "setmainwid.h"
#include "ui_setmainwid.h"

SetMainWid::SetMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetMainWid)
{
    ui->setupUi(this);

    mDevWid[0] = new DevThresholdWid(ui->widget_1);
    mDevWid[1] = new DevThresholdWid(ui->widget_2);
    for(int i=0; i<DEV_NUM; i++) {
        mDevWid[i]->init(i);
    }
}

SetMainWid::~SetMainWid()
{
    delete ui;
}
