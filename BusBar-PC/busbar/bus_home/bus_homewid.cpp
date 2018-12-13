#include "bus_homewid.h"
#include "ui_bus_homewid.h"

BUS_HomeWid::BUS_HomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_HomeWid)
{
    ui->setupUi(this);

    initFun();
    initWidget();
}

BUS_HomeWid::~BUS_HomeWid()
{
    delete ui;
}

void BUS_HomeWid::initFun()
{
    busChangedSlot(0);
    mMaxNum = mBusData->devNum;

    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone())); //实时更新
    connect(this, SIGNAL(busChangedSig(int)), this, SLOT(busChangedSlot(int))); //修改当前母线
}

void BUS_HomeWid::initWidget()
{
    int id=0;
    mBaseNum = 0;

    QObjectList list = children();
    foreach (QObject *obj1, list)
    {
        if(id >= 10) break; //前10
        if (obj1->inherits("QWidget")){
            QWidget *b = qobject_cast<QWidget*>(obj1);
            mBoxWid[id] = new BUS_HomeBoxWid(b);
            BUS_HomeBoxWid *boxWid = mBoxWid[id];
            boxWid->initFun(mBaseNum, id++);
            connect(this, SIGNAL(busChangedSig(int)), boxWid, SLOT(busChangeSlot(int))); //修改母线
        }
    }
    checkBoxBaseNum();

    /* 考虑到不可相加 故隐藏 */
    ui->label->hide();
    ui->curLcd->hide();
    ui->label_2->hide();
    ui->powLcd->hide();
    ui->label_3->hide();
    ui->label_4->hide();
}


void BUS_HomeWid::timeoutDone()
{
    ui->curLcd->display(mBusData->dev[0].data.tg.cur.value/COM_RATE_CUR); //A
    ui->powLcd->display(mBusData->dev[0].data.tg.pow/COM_RATE_POW); //W

    QString name = tr("直");
    if(mBusData->dev[0].dc) name = tr("交");
    ui->name1->setText(name);

    if(mMaxNum != mBusData->devNum) {
        checkBoxBaseNum();
        mMaxNum = mBusData->devNum;
    }
}

void BUS_HomeWid::setBoxBaseNum()
{
    for(int i=0; i<10; ++i)
        mBoxWid[i]->initFun(mBaseNum, i);
}

bool BUS_HomeWid::checkBoxBaseNum()
{
    bool enable = true;
    if(mBaseNum==0) {
        enable = false;
    }
    ui->upBtn->setEnabled(enable);

    int maxNum = (mBaseNum + 1) *10;
    if(maxNum >= mBusData->devNum) {
        enable = false;
    }else {
        enable = true;
    }
    ui->downBtn->setEnabled(enable);

    setBoxBaseNum();
    return enable;
}

void BUS_HomeWid::on_upBtn_clicked()
{
    mBaseNum-- ;
    if(mBaseNum < 0) {
        mBaseNum = 0;
    }
    checkBoxBaseNum();
}

void BUS_HomeWid::on_downBtn_clicked()
{
    mBaseNum++;
    bool ret = checkBoxBaseNum();
    if(!ret) {
        // mBaseNum--;
        // checkBoxBaseNum(); //保持界面-数据统一
    }
}

void BUS_HomeWid::busChangedSlot(int id)
{
    mBusData = BUS_DataPackets::bulid()->getBus(id);
}
