#include "bus_boxdlg.h"
#include "ui_boxdlg.h"

BUS_BoxDlg::BUS_BoxDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BUS_BoxDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("接插箱"), this);
}

BUS_BoxDlg::~BUS_BoxDlg()
{
    delete ui;
}

void BUS_BoxDlg::initBox(int bus, int box)
{
    QString name = BUS_DataPackets::bulid()->getBusName(bus);
    ui->titleLab->setText(name);

    sDataPacket *shm = BUS_DataPackets::bulid()->getBox(bus, box);
    QString version = QString("V%1.%2").arg(shm->version/10).arg(shm->version%10);
    ui->version->setText(version);

    initWid(bus, box);
}

void BUS_BoxDlg::initWid(int bus, int box)
{
    mLineWid = new BUS_BoxLineTableWid(ui->tabWidget);
    mLineWid->initFun(bus, box);
    ui->tabWidget->addTab(mLineWid, tr("各相信息"));

    mLoopWid = new BUS_BoxLoopTableWid(ui->tabWidget);
    mLoopWid->initFun(bus, box);
    ui->tabWidget->addTab(mLoopWid, tr("各回路信息"));
}

void BUS_BoxDlg::on_pushButton_clicked()
{
    this->close();
}
