#include "boxtotalwid.h"
#include "ui_boxtotalwid.h"

BoxTotalWid::BoxTotalWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxTotalWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    ui->AllWid->hide(); //隐藏和 y_MW_2018.4.23
}

BoxTotalWid::~BoxTotalWid()
{
    delete ui;
}


void BoxTotalWid::initFun(int bus, int box)
{
    sDataPacket *shm = get_share_mem();
    mBox = &(shm->data[bus].box[box]);
    mTgBox = &(shm->data[bus].box[box].tgBox);
    mLineTgBox  = &(shm->data[bus].box[box].lineTgBox);
    mEnvData = &(shm->data[bus].box[box].env);
    updateData();
}

void BoxTotalWid::timeoutDone()
{
    updateData();
}
/*
void BoxTotalWid::setTemp(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = &(mEnvData->tem);

    double value = unit->value[id]/COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "°C";
    setTableItem(id, column, str);

    setAlarmStatus(id, column,unit->alarm[id], unit->crAlarm[id]);
}*/

void BoxTotalWid::updateData()
{
    if(mBox->dc){ //交流
        ui->CWid->show();
    }else{
        ui->CWid->hide();
    }

    QString str;
    int i = 0;
   // if(mLineTgBox->vol[i]){
        str= QString::number(mLineTgBox->cur[i]/COM_RATE_CUR, 'f', 1) + "A";
        ui->curA->setText(str);

        str =  QString::number(mLineTgBox->pow[i]/COM_RATE_POW, 'f', 3) + "kW";
        ui->tPowA->setText(str);

        str =  QString::number(mLineTgBox->apPow[i]/COM_RATE_POW, 'f', 3) + "kVA";
        ui->tApPowA->setText(str);

        str =  QString::number(mLineTgBox->pf[i]/COM_RATE_PF, 'f', 2);
        ui->tPfA->setText(str);

        str =  QString::number(mLineTgBox->ele[i]/COM_RATE_ELE, 'f', 1);// + "kWh";
        ui->tEleA->setText(str);

        str = QString::number(mLineTgBox->vol[i]) + "V";
        ui->volA->setText(str);
  /*  }else{
        str= "---";
        ui->curA->setText(str);
        ui->tPowA->setText(str);
        ui->tApPowA->setText(str);
        ui->tPfA->setText(str);
        ui->tEleA->setText(str);
        ui->volA->setText(str);
    }*/
    i = 1;
  //  if(mLineTgBox->vol[i]){
        str= QString::number(mLineTgBox->cur[i]/COM_RATE_CUR, 'f', 1) + "A";
        ui->curB->setText(str);

        str =  QString::number(mLineTgBox->pow[i]/COM_RATE_POW, 'f', 3) + "kW";
        ui->tPowB->setText(str);

        str =  QString::number(mLineTgBox->apPow[i]/COM_RATE_POW, 'f', 3) + "kVA";
        ui->tApPowB->setText(str);

        str =  QString::number(mLineTgBox->pf[i]/COM_RATE_PF, 'f', 2);
        ui->tPfB->setText(str);

        str =  QString::number(mLineTgBox->ele[i]/COM_RATE_ELE, 'f', 1);// + "kWh";
        ui->tEleB->setText(str);

        str = QString::number(mLineTgBox->vol[i]) + "V";
        ui->volB->setText(str);
  /*  }else{
        str= "---";
        ui->curB->setText(str);
        ui->tPowB->setText(str);
        ui->tApPowB->setText(str);
        ui->tPfB->setText(str);
        ui->tEleB->setText(str);
        ui->volB->setText(str);
    }*/
    i = 2;
   // if(mLineTgBox->vol[i]){
        str= QString::number(mLineTgBox->cur[i]/COM_RATE_CUR, 'f', 1) + "A";
        ui->curC->setText(str);
        str =  QString::number(mLineTgBox->pow[i]/COM_RATE_POW, 'f', 3) + "kW";
        ui->tPowC->setText(str);
        str =  QString::number(mLineTgBox->apPow[i]/COM_RATE_POW, 'f', 3) + "kVA";
        ui->tApPowC->setText(str);
        str =  QString::number(mLineTgBox->pf[i]/COM_RATE_PF, 'f', 2);
        ui->tPfC->setText(str);
        str =  QString::number(mLineTgBox->ele[i]/COM_RATE_ELE, 'f', 1);// + "kWh";
        ui->tEleC->setText(str);
        str = QString::number(mLineTgBox->vol[i]) + "V";
        ui->volC->setText(str);
  /*  }else{
        str= "---";
        ui->curC->setText(str);
        ui->tPowC->setText(str);
        ui->tApPowC->setText(str);
        ui->tPfC->setText(str);
        ui->tEleC->setText(str);
        ui->volC->setText(str);
    }*/

    //---------------------------[hexiang]-----------------------------------------

    if(mTgBox->vol){
        str= QString::number(mTgBox->cur/COM_RATE_CUR, 'f', 1) + "A";
        ui->curH->setText(str);

        str =  QString::number(mTgBox->pow/COM_RATE_POW, 'f', 3) + "kW";
        ui->tPowH->setText(str);

        str =  QString::number(mTgBox->apPow/COM_RATE_POW, 'f', 3) + "kVA";
        ui->tApPowH->setText(str);

        str =  QString::number(mTgBox->pf/COM_RATE_PF, 'f', 2);
        ui->tPfH->setText(str);

        str =  QString::number(mTgBox->ele/COM_RATE_ELE, 'f', 1);// + "kWh";
        ui->tEleH->setText(str);

        str = QString::number(mTgBox->vol) + "V";
        ui->volH->setText(str);
    }else{
        str= "---";
        ui->curH->setText(str);
        ui->tPowH->setText(str);
        ui->tApPowH->setText(str);
        ui->tPfH->setText(str);
        ui->tEleH->setText(str);
        ui->volH->setText(str);
    }

    int len = 0;
    sDataUnit *unit = &(mEnvData->tem);
    if(unit->value[0]){
        str =  QString::number(unit->value[0]) + "°C";
        setLabeColor(ui->temA, unit->alarm[0], unit->crAlarm[0]);
        len++;
    }else{
        str = "---";
        setLabeColor(ui->temA, 0, 0);
    }
    ui->temA->setText(str);

    if(unit->value[1]){
        str =  QString::number(unit->value[1]) + "°C";
        setLabeColor(ui->temB, unit->alarm[1], unit->crAlarm[1]);
        len++;
    }else{
        str = "---";
         setLabeColor(ui->temB, 0, 0);
    }
    ui->temB->setText(str);

    if(unit->value[2]){
        str =  QString::number(unit->value[2]) + "°C";
        setLabeColor(ui->temC, unit->alarm[2], unit->crAlarm[2]);
        len++;
    }else{
        str = "---";
        setLabeColor(ui->temC, 0, 0);
    }
    ui->temC->setText(str);

    if(len){
        str =  QString::number((unit->value[0] + unit->value[1] + unit->value[2])/len) + "°C";
    }else{
        str = "---";
    }
    ui->temH->setText(str);

}

void BoxTotalWid::setLabeColor(QLabel *label, int alarm, int crAlarm)
{
    QPalette pa;
    if(alarm) { // 告警
        pa.setColor(QPalette::WindowText,Qt::red);
    } else  if(crAlarm) { // 预警
        pa.setColor(QPalette::WindowText,"#CD7E80");
    } else {
        pa.setColor(QPalette::WindowText,Qt::black);
    }
    label->setPalette(pa);
}
