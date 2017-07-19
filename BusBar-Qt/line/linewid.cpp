#include "linewid.h"
#include "ui_linewid.h"

LineWid::LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWid)
{
    ui->setupUi(this);

    initFun();
    initWid();
}

LineWid::~LineWid()
{
    delete ui;
}

void LineWid::initFun()
{
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[0]);

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void LineWid::initWid()
{
    mTotalWid = new LineTotalWid(ui->totalWid);
    connect(this, SIGNAL(busChangedSig(int)), mTotalWid, SLOT(busChangeSlot(int)));

    mLine[0] = new LineRoadWid(ui->line1Wid);
    mLine[1] = new LineRoadWid(ui->line2Wid);
    mLine[2] = new LineRoadWid(ui->line3Wid);

    for(int i=0; i<3; ++i) {
        LineRoadWid *line  = mLine[i];
        line->initLine(i);
        connect(this, SIGNAL(busChangedSig(int)), line, SLOT(busChangeSlot(int)));
    }
}

void LineWid::timeoutDone()
{
    QString str = QString::number(mData->rate) + "Hz";
    ui->rateLab->setText(str);

    str = QString::number(mData->env.tem.value[0]) + "C";
    ui->temLab->setText(str);
}

