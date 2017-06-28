#include "linewid.h"
#include "ui_linewid.h"

LineWid::LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWid)
{
    ui->setupUi(this);

    initWid();
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    on_comboBox_currentIndexChanged(0);
}

LineWid::~LineWid()
{
    delete ui;
}

void LineWid::initWid()
{
    mTotalWid = new LineTotalWid(ui->totalWid);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), mTotalWid, SLOT(busChangeSlot(int)));

    mLine[0] = new LineRoadWid(ui->line1Wid);
    mLine[1] = new LineRoadWid(ui->line2Wid);
    mLine[2] = new LineRoadWid(ui->line3Wid);

    for(int i=0; i<3; ++i) {
        LineRoadWid *line  = mLine[i];
        line->busChangeSlot(i);
        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), line, SLOT(busChangeSlot(int)));
    }
}

void LineWid::timeoutDone()
{
    QString str = QString::number(mData->rate) + "Hz";
    ui->rateLab->setText(str);

    str = QString::number(mData->env.tem.value[0]) + "C";
    ui->temLab->setText(str);

}

void LineWid::on_comboBox_currentIndexChanged(int index)
{
    mData = &(get_share_mem()->data[index]);
}
