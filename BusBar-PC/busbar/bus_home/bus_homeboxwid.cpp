#include "bus_homeboxwid.h"
#include "ui_bus_homeboxwid.h"


BUS_HomeBoxWid::BUS_HomeBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_HomeBoxWid)
{
    ui->setupUi(this);
    initWid();
    mBoxNum = mBusID = 0;

    timer = new QTimer(this);
    timer->start(1000 + rand()%100); //防止所有对象同时申请刷新
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BUS_HomeBoxWid::~BUS_HomeBoxWid()
{
    delete ui;
}

void BUS_HomeBoxWid::initFun(int base, int id)
{
    mID = base*10 + id+1;
    sDevPackets *shm = BUS_DataPackets::bulid()->getBus(mBusID);
    mBoxNum = shm->devNum;
    mData = &(shm->dev[mID]);
    ui->titleLab->setText(QString::number(mID));
    updateData();
}


void BUS_HomeBoxWid::busChangeSlot(int id)
{
    mBusID = id;
    mData = BUS_DataPackets::bulid()->getBox(id, mBoxNum);
    updateData();
}

/**
 * @brief 更新电流显示
 */
void BUS_HomeBoxWid::updateData()
{
    QPalette pe;
    QString str =  QString::number(mData->data.tg.cur.value/COM_RATE_CUR,'f',1) + "A";
    if(mData->offLine)   // 在线
    {
        switch (mData->alarm) {
        case 2: pe.setColor(QPalette::WindowText,Qt::red);break;
        case 1: pe.setColor(QPalette::WindowText,"#CD7E80");break;
        default: pe.setColor(QPalette::WindowText,Qt::black); break;
        }
    } else {
        str = "---";
    }
    ui->curLab->setText(str);
    ui->curLab->setPalette(pe);
}

void BUS_HomeBoxWid::updateAlarmIcon(QLabel *lab)
{
    QString str = "boxoffine";

    if(mData->offLine)   // 在线
    {
        switch (mData->alarm) {
        case 2: str = "boxalarm";break;
        case 1: str = "boxciralarm";break;
        default: str = "boxonline"; break;
        }

        setBackgroundImage(lab,str);
    }
}

/**
 * @brief 更新告警图片
 */
void BUS_HomeBoxWid::updateAlarmStatus()
{
    updateAlarmIcon(ui->iconLab_1);
    updateAlarmIcon(ui->iconLab_2);
    updateAlarmIcon(ui->iconLab_3);

    bool hidden = false;
    if(mID > mBoxNum) hidden = true;
    this->setHidden(hidden);
}

void BUS_HomeBoxWid::timeoutDone()
{
        updateData();
        updateAlarmStatus();
}

void BUS_HomeBoxWid::on_pushButton_clicked()
{
    BUS_BoxDlg dlg(this);
    dlg.initBox(mBusID, mID);
    dlg.exec();
}

void BUS_HomeBoxWid::initWid()
{
    ui->curLab->hide(); //隐藏和——by_MW_2018.04.23

    QSize size(95,95);
    set_background_icon(this, ":/new/prefix1/image/round.png", size);
}

void BUS_HomeBoxWid::setBackgroundImage(QLabel *lab, QString name)
{
    QString str = QString("border-image: url(:/new/prefix1/image/%1.png);").arg(name);
    lab->setStyleSheet(str);
}
