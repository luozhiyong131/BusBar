#include "subsettingthreshold.h"
#include "ui_subsettingthreshold.h"

SubSettingThreshold::SubSettingThreshold(int bus ,int row ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubSettingThreshold)
{
    ui->setupUi(this);

    mBus = bus;
    mIndex = row + 1;
    mPacket = get_share_mem();
    mShm = new SetShm;

    initWid();

}

SubSettingThreshold::~SubSettingThreshold()
{
    delete ui;
}

void SubSettingThreshold::initWid()
{

    sBoxData *boxData = &(mPacket->data[mBus].box[mIndex]);

    QString busTitle = mPacket->data[mBus].busName;
    QString boxTitle = boxData->boxName;
    ui->label_13->setText(busTitle);
    ui->label_14->setText(boxTitle);

    //L1
    ui->spinBox->setValue(boxData->data.cur.min[0]);
    ui->spinBox_2->setValue(boxData->data.cur.crMin[0]);
    ui->spinBox_3->setValue(boxData->data.cur.crMax[0]);
    ui->spinBox_4->setValue(boxData->data.cur.max[0]);

    //L2
    ui->spinBox_5->setValue(boxData->data.cur.min[1]);
    ui->spinBox_6->setValue(boxData->data.cur.crMin[1]);
    ui->spinBox_7->setValue(boxData->data.cur.crMax[1]);
    ui->spinBox_8->setValue(boxData->data.cur.max[1]);

    //L3
    ui->spinBox_9->setValue(boxData->data.cur.min[2]);
    ui->spinBox_10->setValue(boxData->data.cur.crMin[2]);
    ui->spinBox_11->setValue(boxData->data.cur.crMax[2]);
    ui->spinBox_12->setValue(boxData->data.cur.max[2]);

    //tem
    ui->spinBox_13->setValue(boxData->env.tem.min[0]);
    ui->spinBox_14->setValue(boxData->env.tem.min[0]);
    ui->spinBox_15->setValue(boxData->env.tem.min[0]);
    ui->spinBox_16->setValue(boxData->env.tem.min[0]);

    qDebug() << "boxdata:" << boxData->data.cur.min[0];
}

/**
 * @brief 保存按纽
 */
void SubSettingThreshold::on_pushButton_clicked()
{
    saveData();
    this->close();
}

void SubSettingThreshold::saveData()
{
    getDigData(); //获取界面数据

    DbThresholdItem item;
    item.id = 0 ;
    item.bus = mBus;

    bool ret = ui->checkBox->isChecked();
    if(ret)  //统一设置
    {

        //        for(int i = 1; i < 18 ; i++)
        //            for(j = 0 ; j < 3 ; j++)
        //            {
        //                item.num = (i - 1)*3+j;
        //                item.type = 3;
        //                mShm->setLoopCurAll();
        //            }
    }else  //单独设置
    {
        qDebug() << "单独设置";
        for(int i = 0 ; i <4 ; i++)
        {
            setDbItem(item,&mDigData,i);
            mShm->saveItem(item);
            qDebug() <<" ---" << mPacket->data[mBus].box[mIndex].data.cur.min[0];

        }
    }


}

void SubSettingThreshold::getDigData()
{

    int i = 0 ;
    int j = 0;
    mDigData.digCur[i][j++] = ui->spinBox->value();      //L1
    mDigData.digCur[i][j++] = ui->spinBox_2->value();
    mDigData.digCur[i][j++] = ui->spinBox_3->value();
    mDigData.digCur[i][j++] = ui->spinBox_4->value();

    i=1;
    j=0;
    mDigData.digCur[i][j++] = ui->spinBox_5->value();  //L2
    mDigData.digCur[i][j++] = ui->spinBox_6->value();
    mDigData.digCur[i][j++] = ui->spinBox_7->value();
    mDigData.digCur[i][j++] = ui->spinBox_8->value();

    i=2;
    j=0;
    mDigData.digCur[i][j++] = ui->spinBox_9->value();   //L3
    mDigData.digCur[i][j++] = ui->spinBox_10->value();
    mDigData.digCur[i][j++] = ui->spinBox_11->value();
    mDigData.digCur[i][j++] = ui->spinBox_12->value();

    i=3;
    j=0;
    mDigData.digCur[i][j++] = ui->spinBox_13->value();  //温度
    mDigData.digCur[i][j++] = ui->spinBox_14->value();
    mDigData.digCur[i][j++] = ui->spinBox_15->value();
    mDigData.digCur[i][j++] = ui->spinBox_16->value();

    qDebug() << " 0   :   0 " << mDigData.digCur[0][0];
}

/**
 * @brief SubSettingThreshold::setDbItem
 * @param item
 * @param data
 * @param index 为二维数组的下标，小于3时表示三相，等于表示温度
 */
void SubSettingThreshold::setDbItem(DbThresholdItem &item, digData *data, int index)
{
    qDebug() << "index :" << index;
    if(index <3) //三相
    {
        item.type = 3;
        item.num = (mIndex - 1)*3 + index; //某插接箱某相

        int ret = 0 ;
        item.min = data->digCur[index][ret++];
        item.crmin = data->digCur[index][ret++];
        item.crmax = data->digCur[index][ret++];
        item.max = data->digCur[index][ret++];

        if(index == 0)
            qDebug() << "item.min:" << item.min << item.num;
    }else //温度
    {
        item.type = 5;
        item.num = mIndex; //某插接箱

        int ret = 0 ;
        item.min = data->digCur[4][ret++];
        item.crmin = data->digCur[4][ret++];
        item.crmax = data->digCur[4][ret++];
        item.max = data->digCur[4][ret++];
    }
}
