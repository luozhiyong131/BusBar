#include "in_mainwid.h"
#include "ui_in_mainwid.h"

IN_MainWid::IN_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(ui->groupBox);
    QTimer::singleShot(50,this,SLOT(initFunSLot())); //延时初始化
}

IN_MainWid::~IN_MainWid()
{
    delete ui;
}

void IN_MainWid::initWidget()
{
    mInputTableWid = new IN_InputTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputTableWid);

    mInputThresholdTableWid = new IN_InputThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputThresholdTableWid);

    mTransTableWid = new IN_TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);

    mEnvTableWid = new IN_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
}

void IN_MainWid::initFunSLot()
{
    initWidget();
//    on_realBtn_clicked();

}

void IN_MainWid::on_realBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mInputTableWid);
}

void IN_MainWid::on_thresholdBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mInputThresholdTableWid);
}

void IN_MainWid::on_transBtn_clicked()
{
     ui->stackedWid->setCurrentWidget(mTransTableWid);
}

void IN_MainWid::on_envBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mEnvTableWid);
}
