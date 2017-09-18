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
    setProcessBarColor(ui->progressBar_2,"red");
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

    indexChanged(0);
}

/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void MajorSetting::updateWidget(int index)
{
    mIndex = index; //主路源编号

    sBusData *busData = &(mPacket->data[index]);
    //    ui->lineEdit->setText(busData->busName);

    //    int boxNum = busData->boxNum;
    //    double rateCur = busData->ratedCur/COM_RATE_CUR;

    //    ui->lineEdit_2->setText(QString::number(rateCur));
    //    ui->lineEdit_3->setText(QString::number(boxNum,10));

    sObjData  *objData = &(busData->data);
    ui->label_1_cur->setText(QString::number(objData ->cur.value[0]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_1_vol->setText(QString::number(objData ->vol.value[0]/COM_RATE_VOL,'f', 1)+"V");
    ui->label_2_cur->setText(QString::number(objData ->cur.value[1]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_2_vol->setText(QString::number(objData ->vol.value[1]/COM_RATE_VOL,'f', 1)+"V");
    ui->label_3_cur->setText(QString::number(objData ->cur.value[2]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_3_vol->setText(QString::number(objData ->vol.value[2]/COM_RATE_VOL,'f', 1)+"V");

    setProgressbarValue(ui->progressBar,&(objData->cur),0);
    setProgressbarValue(ui->progressBar_2,&(objData->vol),0);
    setProgressbarValue(ui->progressBar_3,&(objData->cur),1);
    setProgressbarValue(ui->progressBar_4,&(objData->vol),1);
    setProgressbarValue(ui->progressBar_5,&(objData->cur),2);
    setProgressbarValue(ui->progressBar_6,&(objData->vol),2);
}

/**
 * @brief MajorSetting::indexChanged
 * @param index  index 改变，刷新额定电流和插接箱数量
 */
void MajorSetting::indexChanged(int index)
{
    sBusData *busData = &(mPacket->data[index]);
    ui->lineEdit->setText(busData->busName);

    int boxNum = busData->boxNum;
    double rateCur = busData->ratedCur/COM_RATE_CUR;

    ui->lineEdit_2->setText(QString::number(rateCur));
    ui->lineEdit_3->setText(QString::number(boxNum,10));
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

    int cirAlarm = data->crAlarm[index];
    int alarm = data->alarm[index];
    if(alarm == 1)
        setProcessBarColor(bar,"red"); //报警
    else if(cirAlarm == 1)
        setProcessBarColor(bar,"yellow"); //预警
    else
        setProcessBarColor(bar,"green"); //正常

}

/**
 * @brief MajorSetting::on_pushButton_clicked 改变母线名称
 */
void MajorSetting::on_pushButton_clicked()
{
    //    qDebug() << "cliced";
    bool saveSuccess = true;
    DbNameItem item;
    item.bus = mIndex;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    QString name = ui->lineEdit->text();
    if( (!name.isEmpty()) && (!(name.size() > NAME_LEN))) {
        item.name = name;
        mShm->setName(item);
    }else
        saveSuccess = false;

    QString rateCurStr = ui->lineEdit_2->text();
    if((!rateCurStr.isEmpty()) && (cm_isDigitStr(rateCurStr)))
    {
        mShm->setLineRatedCur(mIndex,rateCurStr.toInt() * COM_RATE_CUR);
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查电流输入格式！"));
        saveSuccess = false;
    }

    QString boxNumStr = ui->lineEdit_3->text();
    if((!boxNumStr.isEmpty()) && (cm_isDigitStr(boxNumStr)))
    {
        mShm->setLineBoxNum(mIndex,boxNumStr.toInt());
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查插接箱数量输入格式！"));
        saveSuccess = false;
    }


    if(saveSuccess)
        QMessageBox::information(this,tr("information"),tr("保存成功！"),tr("确定"));
    else
        QMessageBox::information(this,tr("information"),tr("保存失败！"),tr("确定"));
}

/**
 * @brief MajorSetting::setProcessBarColor 设置进度条颜色
 * @param bar
 * @param color
 */
void MajorSetting::setProcessBarColor(QProgressBar *bar, QString color)
{

    QString str = "QProgressBar{border:1px solid #000000;height:20;background:transparent;text-align:center;color:rgb(134,68,54);border-radius:10px;}";
    str += QString(" QProgressBar::chunk{border-radius:10px;border:1px solid black;background-color:%1;margin:0.5px;}").arg(color);
    bar->setStyleSheet(str);
}
