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
}

/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void MajorSetting::updateWidget(int index)
{
    mIndex = index; //主路源编号
    sBusData *busData = &(mPacket->data[index]);

    int dc = busData->box[0].dc;
    if(dc){ //交流
        showSum(3);
    }else{
        int len = busData->box[0].rate ? busData->box[0].rate : 1;
        showSum(len);
    }

    sObjData  *objData = &(busData->box[0].data);
    ui->label_1_cur->setText(QString::number(objData ->cur.value[0]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_1_vol->setText(QString::number(objData ->vol.value[0]/COM_RATE_VOL,'f', 0)+"V");
    ui->label_2_cur->setText(QString::number(objData ->cur.value[1]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_2_vol->setText(QString::number(objData ->vol.value[1]/COM_RATE_VOL,'f', 0)+"V");
    ui->label_3_cur->setText(QString::number(objData ->cur.value[2]/COM_RATE_CUR,'f', 1)+"A");
    ui->label_3_vol->setText(QString::number(objData ->vol.value[2]/COM_RATE_VOL,'f', 0)+"V");

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
        int ret = (value*1.0/max)*100;
        bar->setValue(ret);
    }else
        bar->setValue(0);

    int cirAlarm = data->crAlarm[index];
    int alarm = data->alarm[index];
    if(alarm == 1)
        setProcessBarColor(bar,"red"); //告警
    else if(cirAlarm == 1)
        setProcessBarColor(bar,"yellow"); //预警
    else
        setProcessBarColor(bar,"green"); //正常
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

/*  现实或隐藏Line2
 * By_MW _2018.3.22
 * */
void MajorSetting::upDataLine2(bool show)
{
    if(show){ //显示
        ui->label_20->show();
        ui->label_21->show();
        ui->label_26->show();
        ui->label_19->show();
        ui->label_27->show();
        ui->label_2_cur->show();
        ui->label_2_vol->show();
        ui->progressBar_3->show();
        ui->progressBar_4->show();
    }else{
        ui->label_20->hide();
        ui->label_21->hide();
        ui->label_26->hide();
        ui->label_19->hide();
        ui->label_27->hide();
        ui->label_2_cur->hide();
        ui->label_2_vol->hide();
        ui->progressBar_3->hide();
        ui->progressBar_4->hide();
    }
}

/*  现实或隐藏Line3
 * By_MW _2018.3.22
 * */
void MajorSetting::upDataLine3(bool show)
{
    if(show){ //显示
        ui->label_32->show();
        ui->label_33->show();
        ui->label_34->show();
        ui->label_35->show();
        ui->label_38->show();
        ui->label_3_cur->show();
        ui->label_3_vol->show();
        ui->progressBar_5->show();
        ui->progressBar_6->show();
    }else{
        ui->label_32->hide();
        ui->label_33->hide();
        ui->label_34->hide();
        ui->label_35->hide();
        ui->label_38->hide();
        ui->label_3_cur->hide();
        ui->label_3_vol->hide();
        ui->progressBar_5->hide();
        ui->progressBar_6->hide();
    }
}

void MajorSetting::showSum(int value)
{
    switch (value) {
    case 1:
        upDataLine2(false);
        upDataLine3(false);
        break;
    case 2:
        upDataLine2(true);
        upDataLine3(false);
        break;
    case 3:
        upDataLine2(true);
        upDataLine3(true);
        break;
    default:
        break;
    }
}
