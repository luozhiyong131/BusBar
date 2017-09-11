#include "homewid.h"
#include "ui_homewid.h"
#include "interfacechangesig.h"
#include "beepthread.h"

HomeWid::HomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWid)
{
    ui->setupUi(this);

    isRun = true;
    initFun();
    initWidget();
}

HomeWid::~HomeWid()
{
    delete ui;
}

void HomeWid::initFun()
{
    busChangedSlot(0);
    connect(this, SIGNAL(busChangedSig(int)), this, SLOT(busChangedSlot(int)));
    mMaxNum = mBusData->boxNum;

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));
}

void HomeWid::initWidget()
{
    int id=0;
    mBaseNum = 0;

    QObjectList list = children();
    foreach (QObject *obj1, list)
    {
        if(id >= 10) break;
        if (obj1->inherits("QWidget"))
        {
            QWidget *b = qobject_cast<QWidget*>(obj1);
            mBoxWid[id] = new HomeBoxWid(b);
            HomeBoxWid *boxWid = mBoxWid[id];
            boxWid->initFun(mBaseNum, id++);
            connect(this, SIGNAL(busChangedSig(int)), boxWid, SLOT(busChangeSlot(int)));
        }
    }
    checkBoxBaseNum();
}

void HomeWid::interfaceChangedSlot(int id)
{
    if(id == 1) {
        isRun = true;
    } else {
        isRun = false;
    }
}

void HomeWid::timeoutDone()
{
    if(isRun) {
        ui->curLcd->display(mBusData->tgBus.cur/COM_RATE_CUR);
        ui->powLcd->display(mBusData->tgBus.pow/COM_RATE_POW);

        if(mMaxNum != mBusData->boxNum) {
            checkBoxBaseNum();
            mMaxNum = mBusData->boxNum;
        }
    }
}

void HomeWid::setBoxBaseNum()
{
    for(int i=0; i<10; ++i)
        mBoxWid[i]->initFun(mBaseNum, i);
    BeepThread::bulid()->beep();
}

bool HomeWid::checkBoxBaseNum()
{
    bool enable = true;
    if(mBaseNum==0) {
        enable = false;
    }
    ui->upBtn->setEnabled(enable);

    int maxNum = (mBaseNum + 1) *10;
    if(maxNum >= mBusData->boxNum) {
        enable = false;
    }else {
        enable = true;
    }
    ui->downBtn->setEnabled(enable);
    setBoxBaseNum();
    return enable;
}

void HomeWid::on_upBtn_clicked()
{
    mBaseNum-- ;
    if(mBaseNum < 0) {
        mBaseNum = 0;
    }
    checkBoxBaseNum();
}

void HomeWid::on_downBtn_clicked()
{
    mBaseNum++;
    bool ret = checkBoxBaseNum();
    if(!ret) {
        mBaseNum--;
    }
}

void HomeWid::busChangedSlot(int id)
{
    sDataPacket *shm = get_share_mem();
    mBusData = &(shm->data[id]);
}
