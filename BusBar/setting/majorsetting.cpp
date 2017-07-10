#include "majorsetting.h"
#include "ui_majorsetting.h"

MajorSetting::MajorSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorSetting)
{
    ui->setupUi(this);
    initWidget();

}

MajorSetting::~MajorSetting()
{
    delete ui;
}

void MajorSetting::initWidget()
{
    connect(ui->progressBar,SIGNAL(clicked()),this,SLOT(barClicked()));
    connect(ui->progressBar_2,SIGNAL(clicked()),this,SLOT(barClicked()));
    connect(ui->progressBar_3,SIGNAL(clicked()),this,SLOT(barClicked()));
    connect(ui->progressBar_4,SIGNAL(clicked()),this,SLOT(barClicked()));
    connect(ui->progressBar_5,SIGNAL(clicked()),this,SLOT(barClicked()));
    connect(ui->progressBar_6,SIGNAL(clicked()),this,SLOT(barClicked()));
}

/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void MajorSetting::updateWidget(int index)
{
    mPacket = get_share_mem();
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

void MajorSetting::barClicked()
{
//    QMessageBox::information(this,tr("helolo"),tr("nn"));
    mSettingThroldWid  = new SettingThreshold(this);
    mSettingThroldWid->exec();
}
