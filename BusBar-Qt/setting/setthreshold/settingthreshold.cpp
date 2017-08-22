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
    isBox = false;

    mShm = new SetShm; //操作共享内存
    //    frmNum::Instance()->Init("lightgray",10); // 打开数字键盘

    initWidget();
}

/**
 * @brief SettingThreshold::SettingThreshold  构造函数的重定义
 * @param parent
 */
SettingThreshold::SettingThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingThreshold)
{
    ui->setupUi(this);
    isBox = true;
    mShm = new SetShm; //操作共享内存
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
    if(!isBox)
        saveData();
    else
        saveLoopData();
    this->close();
}

void SettingThreshold::initWidget()
{
    //    qDebug() << "mBus" << mBus << "mIndex" << mIndex;
    sDataPacket *data = share_mem_get(); //获取共享内存
    sDataUnit *unit;
    int aret;

    QString str;

    if(mIsCur)
    {
        unit = &(data->data[mBus].data.cur);
        str = "A";
        aret = COM_RATE_CUR;
    }
    else
    {
        unit = &(data->data[mBus].data.vol);
        str = "V";
        aret = COM_RATE_VOL;
    }

    ui->spinBox->setValue(unit->min[mIndex]/aret);
    ui->spinBox_2->setValue(unit->max[mIndex]/aret);
    ui->spinBox_3->setValue(unit->crMin[mIndex]/aret);
    ui->spinBox_4->setValue(unit->crMax[mIndex]/aret);

    setSuffex(str);

}

/**
 * @brief SettingThreshold::initWidget
 * @param index  当前母线编号
 * @param boxNUm 插接箱编号
 * @param lineNum 相数  0-2,为3则表示当前点击为温度
 */
void SettingThreshold::initWidget(int index , int boxNUm , int lineNum, int temNum)
{
    mBusNum = index;
    mBoxNum = boxNUm;
    mLineNum = lineNum; //保存必要信息，为保存数据到共享内存做准备
    mTemNum = temNum;

    sDataPacket *data = share_mem_get();
    sDataUnit *unit;

    QString str,title;
    if((lineNum >= 0) && (lineNum < 3))
    {
        str = "A";
        title = QString("母线%1插接箱%2相电流%3阈值设置").arg(index+1).arg(boxNUm).arg(lineNum+1);
        unit = &(data->data[index].box[boxNUm].data.cur);
        initData(unit , lineNum);
    }
    else if ((lineNum == 3) && (temNum != 0))
    {
        str = "℃";
        title = QString("母线%1插接箱%2温度%3阈值设置").arg(index+1).arg(boxNUm).arg(temNum);
        unit = &(data->data[index].box[boxNUm].env.tem);
        initData(unit , temNum-1);  //温度只有一个
    }
    else
        str = "X";

    setSuffex(str);
    ui->label->setText(title);
}

/**
 * @brief SettingThreshold::initData  初始化界面数据
 * @param unit  电流或温度数据包
 * @param index 相数
 */
void SettingThreshold::initData(sDataUnit *unit ,int index)
{
    ui->spinBox->setValue(unit->min[index]);
    ui->spinBox_2->setValue(unit->max[index]);
    ui->spinBox_3->setValue(unit->crMin[index]);
    ui->spinBox_4->setValue(unit->crMax[index]);
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
    int aret;

    if(mIsCur)
        aret = COM_RATE_CUR;
    else
        aret  = COM_RATE_VOL;

    item.min = ui->spinBox->value()*aret;
    item.max = ui->spinBox_2->value()*aret;
    item.crmin = ui->spinBox_3->value()*aret;
    item.crmax = ui->spinBox_4->value()*aret;


    bool ret = ui->checkBox->isChecked();
    if(ret) //统一设置
    {
        qDebug() << "统一设置";
        if(mIsCur)
            mShm->setLineCurAll(item);
        else
            mShm->setLineVolAll(item);

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

/**
 * @brief 保存插接箱数据
 */
void SettingThreshold::saveLoopData()
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
        //        mShm->setLineCurAll(item);
        if(mLineNum !=3)
            mShm->setLoopCurAll(item); //电流统一设置
        else
            mShm->setTempAll(item);  //温度统一设置

    }else //单独设置
    {
        qDebug() << "单一设置";
        item.bus = mBusNum;

        if(mLineNum !=3)
        {
            item.type = 3; //插接箱电流
            item.num = (mBoxNum - 1)*3 + mLineNum;
        }
        else
        {
            item.type = 5; //插接箱温度
            item.num = (mBoxNum - 1)*3 + (mTemNum-1) ;
        }
        mShm->saveItem(item);
    }
}

/**
 * @brief SettingThreshold::on_pushButton_cancel_clicked 取消按钮
 */
void SettingThreshold::on_pushButton_cancel_clicked()
{
    this->close();
}
