#include "majorsetting.h"
#include "ui_majorsetting.h"

MajorSetting::MajorSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorSetting)
{
    ui->setupUi(this);

    mIndex = 0;
    initWidget();

}

MajorSetting::~MajorSetting()
{
    delete ui;
}

void MajorSetting::initWidget()
{
    sDataPacket *mPacket = get_share_mem();

    ui->progressBar->setPacket(&(mPacket->data[mIndex].data),true,0);
    connect(ui->progressBar,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));

    ui->progressBar_2->setPacket(&(mPacket->data[mIndex].data),false,0);
    connect(ui->progressBar_2,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));

    ui->progressBar_3->setPacket(&(mPacket->data[mIndex].data),true,0);
    connect(ui->progressBar_3,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));

    ui->progressBar_4->setPacket(&(mPacket->data[mIndex].data),false,0);
    connect(ui->progressBar_4,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));

    ui->progressBar_5->setPacket(&(mPacket->data[mIndex].data),true,0);
    connect(ui->progressBar_5,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));

    ui->progressBar_6->setPacket(&(mPacket->data[mIndex].data),false,0);
    connect(ui->progressBar_6,SIGNAL(clicked(sObjData *data,bool isCur,int index)),this,SLOT(barClicked(sObjData *data,bool isCur,int index)));
}

/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void MajorSetting::updateWidget(int index)
{
    mIndex = index; //主路源编号

    sDataPacket *mPacket = get_share_mem();
    sBusData busData = mPacket->data[0];

    ui->lineEdit->setText(busData.busName);
    ui->lineEdit_2->setText("20");
    ui->lineEdit_3->setText(QString(busData.boxNum,10));

    sObjData  objData = busData.data;
    ui->label_1_cur->setText(QString(objData .cur.value[index],10));
    ui->label_1_vol->setText(QString(objData .vol.value[index],10));
    ui->label_2_cur->setText(QString(objData .cur.value[index],10));
    ui->label_2_vol->setText(QString(objData .vol.value[index],10));
    ui->label_3_cur->setText(QString(objData .cur.value[index],10));
    ui->label_3_vol->setText(QString(objData .vol.value[index],10));

    ui->progressBar->setValue(objData .cur.value[0]/objData.cur.max[0]);
    ui->progressBar_2->setValue(objData .vol.value[0]/objData.vol.max[0]);
    ui->progressBar_3->setValue(objData .cur.value[1]/objData.cur.max[1]);
    ui->progressBar_4->setValue(objData .vol.value[1]/objData.vol.max[1]);
    ui->progressBar_5->setValue(objData .cur.value[2]/objData.cur.max[2]);
    ui->progressBar_6->setValue(objData .vol.value[2]/objData.vol.max[2]);

}

/**
 * @brief MajorSetting::barClicked
 * @param data 阈值相关数据包
 * @param isCur 非电流即电压
 * @param index 电流或电压相数
 */
void MajorSetting::barClicked(sObjData *data,bool isCur,int index)
{
    //    QMessageBox::information(this,tr("helolo"),tr("nn"));
    mSettingThroldWid  = new SettingThreshold(data,isCur,index,this);
    mSettingThroldWid->exec();
}
