#include "homeboxwid.h"
#include "ui_homeboxwid.h"
#include "box/boxdlg.h"

HomeBoxWid::HomeBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeBoxWid)
{
    ui->setupUi(this);
//    initWid();
    mBusID = 0;

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

HomeBoxWid::~HomeBoxWid()
{
    delete ui;
}

void HomeBoxWid::initFun(int base, int id)
{
     mID = base*10 + id+1;
     sDataPacket *shm = get_share_mem();
     mData = &(shm->data[mBusID].box[mID]);
     ui->titleLab->setText(QString::number(mID));
     updateData();
}


void HomeBoxWid::busChangeSlot(int id)
{
    mBusID = id;
    sDataPacket *shm = get_share_mem();
    mData = &(shm->data[id].box[mID]);
    updateData();
}

void HomeBoxWid::updateData()
{
    QPalette pe;
    QString str =  QString::number(mData->tgBox.cur) + "A";
    if(mData->offLine)   // 在线
    {
        if(mData->boxCurAlarm == 2)
            pe.setColor(QPalette::WindowText,Qt::red);
        else  if(mData->boxCurAlarm == 1)
            pe.setColor(QPalette::WindowText,Qt::yellow);
        else
            pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str = "---";
    }
    ui->iconLab->setText(str);
    ui->iconLab->setPalette(pe);
}

void HomeBoxWid::timeoutDone()
{
    updateData();
}

void HomeBoxWid::on_pushButton_clicked()
{
    BoxDlg dlg(0);
    dlg.initBox(mBusID, mID);
    dlg.exec();
}

void HomeBoxWid::initWid()
{
    QPixmap pix;
    pix.load(":/new/prefix1/image/round.png",0,Qt::AvoidDither|Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(QBitmap(pix.mask()));
}
