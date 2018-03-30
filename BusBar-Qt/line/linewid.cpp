#include "linewid.h"
#include "ui_linewid.h"
#include "interfacechangesig.h"

LineWid::LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWid)
{
    ui->setupUi(this);

    mIndex = 0;
    initFun();
    initWid();

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
    mData = &(shm->data[mIndex]);

    isRun = false;
    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void LineWid::initWid()
{
    //    mTotalWid = new LineTotalWid(ui->totalWid);
    //    connect(this, SIGNAL(busChangedSig(int)), mTotalWid, SLOT(busChangeSlot(int)));
    initTotalWid(); //表盘界面

    //三总线界面
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
        QString str;
        if(mData->box[0].dc){ //交流
            str= QString::number(mData->box[0].rate) + "Hz";
            ui->rateLab->setText(str); //频率
            ui->label->setText("频率：");
        }else{
            str= QString::number(mData->box[0].rate) + "路";
            ui->rateLab->setText(str); //频率
            ui->label->setText("输入：");
        }

        //------[版本号]------------
        QString version = QString("V%1.%2").arg(mData->box[0].version/10).arg(mData->box[0].version%10);
        ui->version->setText(version);

        updatePlot();
    }
}


void LineWid::initTotalWid()
{
    QHBoxLayout *layout = new QHBoxLayout(ui->totalWid);

    mCurPlot = new CustomDialPlot(ui->totalWid);
    mVolPlot = new CustomDialPlot(ui->totalWid);
    mPwPlot = new CustomDialPlot(ui->totalWid);
//    mPfPlot = new CustomDialPlot(ui->totalWid);

    layout->addWidget(mVolPlot);
    layout->addWidget(mCurPlot);
    layout->addWidget(mPwPlot);
//    layout->addWidget(mPfPlot);

    mVolPlot->setUnit("V");
    mVolPlot->setRange(0,255);

    mCurPlot->setUnit("A");
    int max = 0;
    for(int i=0; i<3; ++i) max += mData->box[0].data.cur.max[i];
    mCurPlot->setRange(0,max/COM_RATE_CUR + 1);

    mPwPlot->setUnit("kW");
    max *= 255;
    mPwPlot->setRange(0,max/COM_RATE_POW);

//    mPfPlot->setUnit("");
//    mPfPlot->setRange(0,1);
}


void LineWid::updatePlot()
{    
    sDataPacket *shm = get_share_mem();
    sTgObjData *tgBusData = &(shm->data[mIndex].box[0].tgBox);
    mVolPlot->setValue(tgBusData->vol);        //表盘更新 V
    mCurPlot->setValue(tgBusData->cur/COM_RATE_CUR); //A
    mPwPlot->setValue(tgBusData->pow/COM_RATE_POW);  //W
//    mPfPlot->setValue(tgBusData->pf/COM_RATE_PF);
}

void LineWid::indexChanged(int index)
{
    mIndex = index;
    //-------[未随着更新]------------ 故ADD—— By_MW
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[mIndex]);
    //-------------------------------------------
}

