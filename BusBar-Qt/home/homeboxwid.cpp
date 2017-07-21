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
    QColor color;
    if(unit.alarm[id]) {
        str += "box-alarm.png"; //////======== 图片不对
        color = QColor(204,29,26); //红色
    } else if(unit.crAlarm[id]) {
        str += "box-ciralarm.png";
        color = QColor("232,157,18"); //黄色
    } else {
        str += "box-online.png";
        color = QColor("34,139,34"); //绿色
    }
    //   set_background_icon(lab, str, QSize(20,40));
    set_background_color(lab,color);
}

/**
 * @brief 更新报警图片
 */
void HomeBoxWid::updateAlarmStatus()
{
    int id = 0;
    //    mData->data.lineNum ;
    if(mData->offLine) {
        updateAlarmIcon(ui->iconLab_1,  mData->data.cur, id++);
        updateAlarmIcon(ui->iconLab_2,  mData->data.cur, id++);
        updateAlarmIcon(ui->iconLab_3,  mData->data.cur, id++);
    } else { // 离线
        QString str = ":/new/prefix1/image/box-offine.png";  //////======== 图片不对
        QColor color("229,229,229"); //灰色
        //        QColor color = QColor(204,29,26); //红色
        //        set_background_icon(ui->iconLab_1, str);
        //        set_background_icon(ui->iconLab_2, str);
        //        set_background_icon(ui->iconLab_3, str);
        set_background_color(ui->iconLab_1, color);
        set_background_color(ui->iconLab_2, color);
        set_background_color(ui->iconLab_3, color);
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
    //    QColor color("255,255,255");
    //    set_background_color(ui->iconLab_1, color);
    //    set_background_color(ui->iconLab_2, color);
    //    set_background_color(ui->iconLab_3, color);
    QSize size(95,95);
    set_background_icon(this, ":/new/prefix1/image/round.png", size);
}
