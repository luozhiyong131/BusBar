#include "homeboxwid.h"
#include "ui_homeboxwid.h"
#include "box/boxdlg.h"

HomeBoxWid::HomeBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeBoxWid)
{
    ui->setupUi(this);
    initWid();
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

/**
 * @brief 更新电流显示
 */
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
    ui->curLab->setText(str);
    ui->curLab->setPalette(pe);
}

void HomeBoxWid::updateAlarmIcon(QLabel *lab, sDataUnit &unit, int id)
{
    QString str = ":/new/prefix1/image/";
    if(unit.alarm[id]) {
        str += "round.png"; //////======== 图片不对
    } else if(unit.crAlarm[id]) {
        str += "round.png";
    } else {
        str += "round.png";
    }

   set_background_icon(lab, str, QSize(20,40));
}

/**
 * @brief 更新报警图片
 */
void HomeBoxWid::updateAlarmStatus()
{
    int id = 0;
    if(mData->offLine) {
        updateAlarmIcon(ui->iconLab_1,  mData->data.cur, id++);
        updateAlarmIcon(ui->iconLab_2,  mData->data.cur, id++);
        updateAlarmIcon(ui->iconLab_3,  mData->data.cur, id++);
    } else { // 离线
        QString str = ":/new/prefix1/image/round.png";  //////======== 图片不对
        set_background_icon(ui->iconLab_1, str);
        set_background_icon(ui->iconLab_2, str);
        set_background_icon(ui->iconLab_3, str);
    }
}

void HomeBoxWid::timeoutDone()
{
    updateData();
    updateAlarmStatus();
}

void HomeBoxWid::on_pushButton_clicked()
{
    BoxDlg dlg(0);
    dlg.initBox(mBusID, mID);
    dlg.exec();
}

void HomeBoxWid::initWid()
{
    set_background_icon(this, ":/new/prefix1/image/round.png", QSize(83,81));
}
