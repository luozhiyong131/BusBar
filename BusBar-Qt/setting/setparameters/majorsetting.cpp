#include "majorsetting.h"
#include "ui_majorsetting.h"

MajorSetting::MajorSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorSetting)
{
    ui->setupUi(this);

    mPacket = get_share_mem();
    mShm = new SetShm;
    mIndex = 0;
    initWidget();
}

MajorSetting::~MajorSetting()
{
    delete ui;
}

void MajorSetting::initWidget()
{
    ui->progressBar->setPacket(true,0);
    connect(ui->progressBar,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));

    ui->progressBar_2->setPacket(false,0);
    connect(ui->progressBar_2,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));

    ui->progressBar_3->setPacket(true,1);
    connect(ui->progressBar_3,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));

    ui->progressBar_4->setPacket(false,1);
    connect(ui->progressBar_4,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));

    ui->progressBar_5->setPacket(true,2);
    connect(ui->progressBar_5,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));

    ui->progressBar_6->setPacket(false,2);
    connect(ui->progressBar_6,SIGNAL(clicked(bool ,int )),this,SLOT(barClicked(bool ,int )));
}

/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void MajorSetting::updateWidget(int index)
{
    mIndex = index; //主路源编号
    sBusData *busData = &(mPacket->data[index]);

    ui->lineEdit->setText(busData->busName);
    ui->lineEdit_2->setText(QString::number(busData->ratedCur,10));
    ui->lineEdit_3->setText(QString(busData->boxNum,10));

    sObjData  *objData = &(busData->data);
    ui->label_1_cur->setText(QString(objData ->cur.value[0],10));
    ui->label_1_vol->setText(QString(objData ->vol.value[0],10));
    ui->label_2_cur->setText(QString(objData ->cur.value[1],10));
    ui->label_2_vol->setText(QString(objData ->vol.value[1],10));
    ui->label_3_cur->setText(QString(objData ->cur.value[2],10));
    ui->label_3_vol->setText(QString(objData ->vol.value[2],10));

    setProgressbarValue(ui->progressBar,&(objData->cur),0);
    setProgressbarValue(ui->progressBar_2,&(objData->vol),0);
    setProgressbarValue(ui->progressBar_3,&(objData->cur),1);
    setProgressbarValue(ui->progressBar_4,&(objData->vol),1);
    setProgressbarValue(ui->progressBar_5,&(objData->cur),2);
    setProgressbarValue(ui->progressBar_6,&(objData->vol),2);
}

/**
 * @brief MajorSetting::barClicked
 * @param data 阈值相关数据包
 * @param isCur 非电流即电压
 * @param index 电流或电压相数
 */
void MajorSetting::barClicked(bool isCur,int index)
{
    //    QMessageBox::information(this,tr("helolo"),tr("nn"));
    mSettingThroldWid  = new SettingThreshold(mIndex,isCur,index,this);
    mSettingThroldWid->exec();
}

/**
 * @brief MajorSetting::setProgressbarValue
 * @param bar
 * @param index 相位
 */
void MajorSetting::setProgressbarValue(QProgressBar *bar, sDataUnit *data, int index)
{
    int max = data->max[index];
    if(max > 0)
    {
        int value = data->value[index];
        int ret = (value/max)*100;
        bar->setValue(ret);
    }else
        bar->setValue(0);
}

/**
 * @brief MajorSetting::on_pushButton_clicked 改变母线名称
 */
void MajorSetting::on_pushButton_clicked()
{
    qDebug() << "cliced";
    DbNameItem item;
    item.bus = mIndex;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    QString name = ui->lineEdit->text();
    if( (!name.isEmpty()) && (!(name.size() > NAME_LEN))) {
        item.name = name;
        mShm->setName(item);
    }
}
