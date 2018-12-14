#include "bus_linewid.h"
#include "ui_bus_linewid.h"
#include "bus_thd/bus_thdmaindlg.h"

BUS_LineWid::BUS_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_LineWid)
{
    ui->setupUi(this);

    mLineTable = new BUS_LineTableWid(ui->widget) ;
    indexChanged(0);

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    connect(this, SIGNAL(busChangedSig(int)), this, SLOT(indexChanged(int)));
}

BUS_LineWid::~BUS_LineWid()
{
    delete ui;
}

void BUS_LineWid::timeoutDone()
{
    QString str;
    if(mDev->dc){ //交流
        str= QString::number(mDev->hz) + "Hz";
        ui->rateLab->setText(str); //频率
        ui->label->setText("频率：");

        ui->thdBtn->setHidden(false);
    }else{
        str= QString::number(mDev->hz) + "路";
        ui->rateLab->setText(str); //频率
        ui->label->setText("输入：");

        ui->thdBtn->setHidden(true);
    }

    QString version = QString("V%1.%2").arg(mDev->version/10).arg(mDev->version%10);
    ui->version->setText(version);
}

void BUS_LineWid::indexChanged(int index)
{
    mIndex = index;
    mDev = BUS_DataPackets::bulid()->getBox(index, 0);
    mLineTable->initFun(index, 0);
}

void BUS_LineWid::on_thdBtn_clicked()
{
    BUS_ThdMainDlg dlg(this);
    dlg.initBus(mIndex);
    dlg.exec();
}
