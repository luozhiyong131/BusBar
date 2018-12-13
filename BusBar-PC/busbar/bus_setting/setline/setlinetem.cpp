#include "setlinetem.h"
#include "ui_setlinetem.h"

SetLineTem::SetLineTem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetLineTem)
{
    ui->setupUi(this);
    indexChanged(0);
    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

SetLineTem::~SetLineTem()
{
    delete ui;
}


void SetLineTem::updateWid()
{
    QPushButton *btn[] ={ui->temBtn_1, ui->temBtn_2, ui->temBtn_3};

    for(int i=0; i<SENOR_NUM; ++i) {
        QString str = startBoxTem->tem[i].value ?  QString::number(startBoxTem->tem[i].value,10)+"℃" : "---";
        btn[i]->setText(str);
    }
}

void SetLineTem::indexChanged(int index)
{
    mBus = index;
    startBoxTem = &(BUS_DataPackets::bulid()->getBox(bus, 0)->data.env); //获取共享内存
}


void SetLineTem::timeoutDone()
{
    updateWid();
}

void SetLineTem::setTem(int id)
{
    sThresholdItem item;
    item.bus = mBus;
    item.box = 0;
    item.num = id;
    item.type = 3;

    SetThresholdDlg dlg(this);
    dlg.set(item);
    dlg.exec();
}

void SetLineTem::on_temBtn_1_clicked()
{
    setTem(0);
}

void SetLineTem::on_temBtn_2_clicked()
{
    setTem(1);
}

void SetLineTem::on_temBtn_3_clicked()
{
    setTem(2);
}
