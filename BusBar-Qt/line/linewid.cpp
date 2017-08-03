#include "linewid.h"
#include "ui_linewid.h"
#include "interfacechangesig.h"

LineWid::LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWid)
{
    ui->setupUi(this);

    initFun();
    initWid();

    mIndex = 0;
    connect(this, SIGNAL(busChangedSig(int)), this, SLOT(indexChanged(int)));
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));
}

LineWid::~LineWid()
{
    delete ui;
}

void LineWid::initFun()
{
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[0]);
    isRun = false;
    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void LineWid::initWid()
{
    //    mTotalWid = new LineTotalWid(ui->totalWid);
    //    connect(this, SIGNAL(busChangedSig(int)), mTotalWid, SLOT(busChangeSlot(int)));
    initTotalWid();

    mLine[0] = new LineRoadWid(ui->line1Wid);
    mLine[1] = new LineRoadWid(ui->line2Wid);
    mLine[2] = new LineRoadWid(ui->line3Wid);

    for(int i=0; i<3; ++i) {
        LineRoadWid *line  = mLine[i];
        line->initLine(i);
        connect(this, SIGNAL(busChangedSig(int)), line, SLOT(busChangeSlot(int)));
    }
}


void LineWid::interfaceChangedSlot(int id)
{
    if(id == 2) {
        isRun = true;
    } else {
        isRun = false;
    }
}

void LineWid::timeoutDone()
{
    if(isRun) {
        QString str = QString::number(mData->rate) + "Hz";
        ui->rateLab->setText(str);

        str = QString::number(mData->env.tem.value[0]) + "C";
        ui->temLab->setText(str);

        updatePlot();
    }

    //    onUpdateDials();
}

void LineWid::initTotalWid()
{
    QHBoxLayout *layout = new QHBoxLayout(ui->totalWid);

    mCurPlot = new CustomDialPlot(ui->totalWid);
    //    mVolPlot = new CustomDialPlot(ui->totalWid);
    mPwPlot = new CustomDialPlot(ui->totalWid);
    mPfPlot = new CustomDialPlot(ui->totalWid);

    layout->addWidget(mCurPlot);
    //    layout->addWidget(mVolPlot);
    layout->addWidget(mPwPlot);
    layout->addWidget(mPfPlot);

    mCurPlot->setUnit("A");
    //    mVolPlot->setUnit("V");
    mPwPlot->setUnit("kVA");
    mPfPlot->setUnit("kWh");

    mCurPlot->setRange(0,100);
}

void LineWid::onUpdateDials()
{
    double dValue = 0;

    dValue = rand()%(mCurPlot->getMax());
    mCurPlot->setValue(dValue);

}

void LineWid::updatePlot()
{
    sDataPacket *shm = get_share_mem();
    sTgObjData *tgBusData = &(shm->data[mIndex].tgBus);

    mCurPlot->setValue(tgBusData->cur);
    mPwPlot->setValue(tgBusData->pow);
    mPfPlot->setValue(tgBusData->pf);
}

void LineWid::indexChanged(int index)
{
    mIndex = index;
}

