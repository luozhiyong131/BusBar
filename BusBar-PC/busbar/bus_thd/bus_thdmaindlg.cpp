#include "bus_thdmaindlg.h"
#include "ui_bus_thdmaindlg.h"

BUS_ThdMainDlg::BUS_ThdMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BUS_ThdMainDlg)
{
    ui->setupUi(this);

    mChartWid = new BUS_ThdChartWid(ui->chartwid);
    mTableWid = new ThdTableWid(ui->tablewid);

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BUS_ThdMainDlg::~BUS_ThdMainDlg()
{
    delete ui;
}

void BUS_ThdMainDlg::initBus(int id)
{
    mBusData = BUS_DataPackets::bulid()->getBus(id);
    on_volAbtn_clicked();
}


void BUS_ThdMainDlg::timeoutDone()
{
    QString str = QString::number((*mLineThd/100.0),'f', 2) + " %";
    ui->thdLab->setText(str);

    mChartWid->updateData(mThd, 30);
    mTableWid->updateData(mThd, 30);
}

void BUS_ThdMainDlg::setLine(int i, int l)
{
    if(i) {
        mThd = mBusData->thd[l].curThd;
        mLineThd = &(mBusData->dev[0].data.line[l].curThd);
    } else {
        mThd = mBusData->thd[l].volThd;
        mLineThd = &(mBusData->dev[0].data.line[l].volThd);
    }
    timeoutDone();
}

void BUS_ThdMainDlg::on_volAbtn_clicked()
{
    setLine(0, 0);
}

void BUS_ThdMainDlg::on_volBbtn_clicked()
{
    setLine(0, 1);
}

void BUS_ThdMainDlg::on_volCbtn_clicked()
{
    setLine(0, 2);
}

void BUS_ThdMainDlg::on_curAbtn_clicked()
{
    setLine(1, 0);
}

void BUS_ThdMainDlg::on_curBbtn_clicked()
{
     setLine(1, 1);
}

void BUS_ThdMainDlg::on_curCbtn_clicked()
{
    setLine(1, 2);
}

void BUS_ThdMainDlg::on_quitBtn_clicked()
{
    this->close();
}
