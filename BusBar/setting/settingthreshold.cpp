#include "settingthreshold.h"
#include "ui_settingthreshold.h"

SettingThreshold::SettingThreshold(int bus,bool isCur,int index ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingThreshold)
{
    ui->setupUi(this);

    mBus = bus;
    mIsCur = isCur;
    mIndex = index;

    mShm = new SetShm; //操作共享内存

    initWidget();
}

SettingThreshold::~SettingThreshold()
{
    delete ui;
}

/**
 * @brief 点击保存按钮
 */
void SettingThreshold::on_pushButton_clicked()
{
    saveData();
    this->close();
}

void SettingThreshold::initWidget()
{
//    qDebug() << "mBus" << mBus << "mIndex" << mIndex;
    sDataPacket *data = share_mem_get(); //获取共享内存
    sDataUnit *unit;


    QString str;

    if(mIsCur)
    {
        unit = &(data->data[mBus].data.cur);
        str = "A";
    }
    else
    {
        unit = &(data->data[mBus].data.vol);
        str = "V";
    }

    ui->spinBox->setValue(unit->min[mIndex]);
    ui->spinBox_2->setValue(unit->max[mIndex]);
    ui->spinBox_3->setValue(unit->crMin[mIndex]);
    ui->spinBox_4->setValue(unit->crMax[mIndex]);

    setSuffex(str);

}

void SettingThreshold::setSuffex(QString str)
{
    ui->spinBox->setSuffix(str);
    ui->spinBox_2->setSuffix(str);
    ui->spinBox_3->setSuffix(str);
    ui->spinBox_4->setSuffix(str);
}

/**
 * @brief 保存数据
 */
void SettingThreshold::saveData()
{
    DbThresholdItem item;

    item.min = ui->spinBox->value();
    item.max = ui->spinBox_2->value();
    item.crmin = ui->spinBox_3->value();
    item.crmax = ui->spinBox_4->value();


    bool ret = ui->checkBox->isChecked();
    if(ret) //统一设置
    {
        qDebug() << "统一设置";
        mShm->setLineCurAll(item);

    }else //单独设置
    {
        qDebug() << "单一设置";
        item.bus = mBus;

        if(mIsCur)
            item.type = 2; //电流
        else
            item.type = 1; //电压

        item.num = mIndex;

        mShm->saveItem(item);

    }
}




