#include "setlineitem.h"
#include "ui_setlineitem.h"

SetLineItem::SetLineItem(QWidget *parent, bool flag) :
    QWidget(parent),
    ui(new Ui::SetLineItem)
{
    ui->setupUi(this);
    mBus = mLine = 0;
    mFlag = flag;
    mPacket = get_share_mem();

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    connect(ui->curBar,SIGNAL(clicked()),this,SLOT(curBarClicked()));
    if(mFlag)
        connect(ui->volBar,SIGNAL(clicked()),this,SLOT(volBarClicked()));
    else
    {
        ui->label_2->hide();
        ui->label_14->hide();
        ui->volBar->hide();
        ui->volLab->hide();
    }
}

SetLineItem::~SetLineItem()
{
    delete ui;
}

void SetLineItem::timeoutDone()
{
    updateWidget(mBus, mLine);
}


/**
 * @brief 主路源变化，刷新界面
 * @param index
 */
void SetLineItem::updateWidget(int bus, int line)
{
    QString str = "L ";
    sBusData *busData = &(mPacket->data[bus]);
    int dc = busData->box[0].dc;
    if(!dc){
        int len = busData->box[0].rate ? busData->box[0].rate : 1;
        if(line>len) this->hide();
        str = "D ";
    }else{  //交流
        this->show();
    }

    sObjData  *objData = &(busData->box[0].data);
    ui->curLab->setText(QString::number(objData ->cur.value[line]/COM_RATE_CUR,'f', 1)+"A");
    setProgressbarValue(ui->curBar,&(objData->cur),line);
    if(mFlag && mLine <= 2)
    {
        ui->volLab->setText(QString::number(objData ->vol.value[line]/COM_RATE_VOL,'f', 0)+"V");
        setProgressbarValue(ui->volBar,&(objData->vol),line);
        ui->nameLab->setText(str+ QString::number(mLine+1));
        str = QString::number(mLine*2+1);
        ui->label_1->setText(str);
        str = QString::number(mLine*2+2);
        ui->label_2->setText(str);
    }
    else if(!mFlag && mLine == 3)
    {
        str = QString::number(mLine*2+1);
        ui->label_1->setText(str);
        ui->nameLab->setFixedHeight(21);
        ui->nameLab->setText("N ");
    }
}


void SetLineItem::setProgressbarValue(QProgressBar *bar, sDataUnit *data, int index)
{
    if(mFlag)
    {
        int max = data->max[index];
        if(max > 0)
        {
            double value = data->value[index]*1.0;
            int ret = (value/max)*100;
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
    else
    {
        bool flag = sys_configFile_open();
        if(flag)
        {
            int max = sys_configFile_readInt("NLineMax");
            int min = sys_configFile_readInt("NLineMin");

            double value = data->value[index]*1.0;
            int compare = data->value[index]*10;
            if(max > 0)
            {
                int ret = (value/(max-min))*100;
                bar->setValue(ret);
            }else{
                bar->setValue(0);
            }
            if(compare > max*10 ||compare < min*10 )
                setProcessBarColor(bar,"red"); //告警
            else
                setProcessBarColor(bar,"green"); //正常
        }
        sys_configFile_close();
    }

}

void SetLineItem::setProcessBarColor(QProgressBar *bar, QString color)
{

    QString str = "QProgressBar{border:1px solid #000000;height:20;background:transparent;text-align:center;color:rgb(134,68,54);border-radius:10px;}";
    str += QString(" QProgressBar::chunk{border-radius:10px;border:1px solid black;background-color:%1;margin:0.5px;}").arg(color);
    bar->setStyleSheet(str);
}

void SetLineItem::curBarClicked()
{
    BeepThread::bulid()->beep();

    sThresholdItem item;
    item.bus = mBus;
    item.box = 0;
    item.num = mLine;
    item.type = 2;

    SetThresholdDlg dlg(this);
    dlg.set(item,mFlag);
    dlg.exec();
}

void SetLineItem::volBarClicked()
{
    BeepThread::bulid()->beep();

    sThresholdItem item;
    item.bus = mBus;
    item.box = 0;
    item.num = mLine;
    item.type = 1;

    SetThresholdDlg dlg(this);
    dlg.set(item,true);
    dlg.exec();
}
