#include "homewid.h"
#include "ui_homewid.h"

HomeWid::HomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWid)
{
    ui->setupUi(this);

    mEmailWid = new EmailWid(ui->widget);
}

HomeWid::~HomeWid()
{
    delete ui;
}
