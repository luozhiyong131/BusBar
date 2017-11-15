#include "logmainwid.h"
#include "ui_logmainwid.h"

LogMainWid::LogMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogMainWid)
{
    ui->setupUi(this);
    initWidget();
}

LogMainWid::~LogMainWid()
{
    delete ui;
}


void LogMainWid::initWidget()
{
    mCabEleWid = new LogCabEleWid(ui->stackedWid);
    ui->stackedWid->addWidget(mCabEleWid);

    mDevWid = new LogDevWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevWid);

    mAlarmWid = new LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mAlarmWid);
    connect(LogSignal::get(), SIGNAL(logTypeSig(int)), this,SLOT(logTypeSlot(int)));
}

void LogMainWid::logTypeSlot(int type)
{
    switch (type) {
    case 0:
        ui->stackedWid->setCurrentWidget(mCabEleWid);
        break;

    case 1:
        ui->stackedWid->setCurrentWidget(mDevWid);
        break;

    case 2:
        ui->stackedWid->setCurrentWidget(mAlarmWid);
        break;
    default:
        break;
    }
}
