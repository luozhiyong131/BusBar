#include "settingthreshold.h"
#include "ui_settingthreshold.h"

#include "shm/setbox.h"

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


void SettingThreshold::initWidget()
{
    //    qDebug() << "mBus" << mBus << "mIndex" << mIndex;
    sDataPacket *data = share_mem_get(); //获取共享内存
    sDataUnit *unit;
    int aret;

    QString str;

    if(mIsCur)
    {
        unit = &(data->data[mBus].box[0].data.cur);
        str = "A";
        aret = COM_RATE_CUR;
    }
    else
    {
        unit = &(data->data[mBus].box[0].data.vol);
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
void SettingThreshold::initWidget(int index , int boxNUm , int lineNum, int temNum ,bool isStartBox)
{
    mBusNum = index;
    mBoxNum = boxNUm;
    mLineNum = lineNum; //保存必要信息，为保存数据到共享内存做准备
    mTemNum = temNum;
    isStart = isStartBox;

    sDataPacket *data = share_mem_get();
    sDataUnit *unit;
    int rate;
    QString str,title;

    if((lineNum > 0) && (lineNum < 10) && (temNum == 0))
    {
        str = "A";
        rate = COM_RATE_CUR;
        title = tr("母线%1 接插箱%2 L%3 电流设置").arg(index+1).arg(boxNUm).arg(lineNum);
        unit = &(data->data[index].box[boxNUm].data.cur);
        initData(unit , lineNum -1,rate);
    }
    else if ((temNum > 0) && (temNum < 10) && (lineNum == 0))
    {
        str = "℃";
        rate = COM_RATE_TEM;
        title = tr("母线%1 接插箱%2 温度%3设置").arg(index+1).arg(boxNUm).arg(temNum);
        unit = &(data->data[index].box[boxNUm].env.tem);
        initData(unit , temNum-1 ,rate);
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
void SettingThreshold::initData(sDataUnit *unit ,int index,int rate)
{
    ui->spinBox->setValue(unit->min[index]/rate);
    ui->spinBox_2->setValue(unit->max[index]/rate);
    ui->spinBox_3->setValue(unit->crMin[index]/rate);
    ui->spinBox_4->setValue(unit->crMax[index]/rate);
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

    if(!checkData(item.min,item.crmin,item.crmax,item.max))
        return;

    item.bus = mBus;
    if(mIsCur)
        item.type = 2; //电流
    else
        item.type = 1; //电压
    item.num = mIndex;
    bool ret = ui->checkBox->isChecked();
    if(ret) //统一设置
    {
        //qDebug() << "统一设置";
        if(mIsCur){
            mShm->setLineCurAll(item);
        }else{
            mShm->setLineVolAll(item);
        }
        if(!SetBOXThread::bulid()->send(2, item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }

    }else //单独设置
    {
       // qDebug() << "单一设置";
        if(!SetBOXThread::bulid()->send(1,item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
        mShm->saveItem(item);
    }
}

/**
 * @brief 保存插接箱数据
 */
void SettingThreshold::saveLoopData()
{
    DbThresholdItem item;
    int rate;

    if((mLineNum != 0) && (mTemNum == 0))
        rate = COM_RATE_CUR;
    else if((mLineNum == 0) && (mTemNum != 0))
        rate = COM_RATE_TEM;

    item.min = ui->spinBox->value()*rate;
    item.max = ui->spinBox_2->value()*rate;
    item.crmin = ui->spinBox_3->value()*rate;
    item.crmax = ui->spinBox_4->value()*rate;

    if(!checkData(item.min,item.crmin,item.crmax,item.max))
        return;
    item.bus = mBusNum;

    if((mLineNum != 0) && (mTemNum == 0))
    {
        item.type = 3; //插接箱电流
        item.num = (mBoxNum - 1)*LINE_NUM + (mLineNum -1);
    }
    else if((mLineNum == 0) && (mTemNum != 0))
    {
        if(isStart)
        {
            item.type = 4;
            item.num =  mTemNum-1;
        }
        else
        {
            item.type = 5; //插接箱温度
            item.num = (mBoxNum - 1)*SENSOR_NUM + (mTemNum-1) ;
        }
    }
    bool ret = ui->checkBox->isChecked();
    if(ret) //统一设置
    {
       // qDebug() << "统一设置";
        if(!SetBOXThread::bulid()->send(2,item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
        if((mLineNum != 0) && (mTemNum == 0))
            mShm->setLoopCurAll(item); //电流统一设置
        else if((mLineNum == 0) && (mTemNum != 0))
            mShm->setTempAll(item);  //温度统一设置

    }else //单独设置
    {
       // qDebug() << "单一设置";
        if(!SetBOXThread::bulid()->send(1,item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
        mShm->saveItem(item);
    }
}


void SettingThreshold::on_cancelBtn_clicked()
{
    this->close();
}

void SettingThreshold::on_saveBtn_clicked()
{
    if(!isBox)
        saveData();
    else
        saveLoopData();

    on_cancelBtn_clicked();
}

bool SettingThreshold::checkData(int min, int crmin, int crmax, int max)
{

//    qDebug() << "checkdata-------------";
    if(min > crmin )
    {
        QMessageBox::warning(this,tr("waring"),tr("最小值大于临界下限！"),tr("OK"));
        return false;
    }else if(min > crmax)
    {
        QMessageBox::warning(this,tr("waring"),tr("最小值大于临界上限！"),tr("OK"));
        return false;
    }else if(min > max)
    {
        QMessageBox::warning(this,tr("waring"),tr("最小值大于最大值！"),tr("OK"));
        return false;
    }else if(crmin > crmax)
    {
        QMessageBox::warning(this,tr("waring"),tr("临界下限大于临界上限！"),tr("OK"));
        return false;
    }else if(crmin > max)
    {
        QMessageBox::warning(this,tr("waring"),tr("临界下限大于最大值！"),tr("OK"));
        return false;
    }else if(crmax > max)
    {
        QMessageBox::warning(this,tr("waring"),tr("临界上限大于最大值！！"),tr("OK"));
        return false;
    }

    return true;
}
