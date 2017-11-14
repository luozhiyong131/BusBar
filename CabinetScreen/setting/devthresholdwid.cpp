#include "devthresholdwid.h"
#include "ui_devthresholdwid.h"

DevThresholdWid::DevThresholdWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevThresholdWid)
{
    ui->setupUi(this);

    mLine = 0;
    init(0);
    initWid();

    timer = new QTimer(this);
    timer->start(5*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

DevThresholdWid::~DevThresholdWid()
{
    delete ui;
}

void DevThresholdWid::init(int id)
{
    sDataPacket *packet = get_dev_dataPacket();
    mDevData = &(packet->dev[id]);
}

void DevThresholdWid::initWid()
{
    QString str = "---";

    ui->volLab->setText(str);
    ui->curLab->setText(str);

    ui->volMinSpinBox->setValue(0);
    ui->volMaxSpinBox->setValue(0);

    ui->curMinSpinBox->setValue(0);
    ui->curMaxSpinBox->setValue(0);

    enabledSpinBox(false);
}

void DevThresholdWid::enabledSpinBox(bool en)
{
    ui->volMinSpinBox->setEnabled(en);
    ui->volMaxSpinBox->setEnabled(en);
    ui->curMinSpinBox->setEnabled(en);
    ui->curMaxSpinBox->setEnabled(en);
}



void DevThresholdWid::updateWid(int line)
{
    if(mDevData->offLine > 0) {

    } else {
        initWid();
    }
}

void DevThresholdWid::timeoutDone()
{

}


void DevThresholdWid::on_saveBtn_clicked()
{

}
