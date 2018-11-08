#include "setthresholddlg.h"
#include "ui_setthresholddlg.h"

SetThresholdDlg::SetThresholdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetThresholdDlg)
{
    ui->setupUi(this);
}

SetThresholdDlg::~SetThresholdDlg()
{
    delete ui;
}


void SetThresholdDlg::initSpinBox(sThresholdItem &item)
{
    ui->minBox->setValue(item.min);
    ui->maxBox->setValue(item.max);

    int range = 63;
    QString str = "A";
    switch (item.type) {
    case 1:  str = "V"; range = 400;  break;
    case 2: if(!item.box) range = 630; str = "A";  break;
    case 3: str = "℃"; range = 99;  break;
    }

    ui->minBox->setSuffix(str);
    ui->maxBox->setSuffix(str);

    ui->minBox->setMaximum(range);
    ui->maxBox->setMaximum(range);
}

void SetThresholdDlg::setTitle(sThresholdItem &item)
{
    QString str;
    switch (item.type) {
    case 1: str = tr("电压"); break;
    case 2: str = tr("电流"); break;
    case 3: str = tr("温度"); break;
    }

    sBoxData *dev = &(share_mem_get()->data[item.bus].box[item.box]); //获取共享内存
    QString nameStr = QString("插接箱%1").arg(dev->boxName);
    if(item.box == 0) nameStr = "始端箱";;

    QString busName = share_mem_get()->data[item.bus].busName;
    QString title = tr("母线%1 %2 输入%3 %4设置").arg(busName).arg(nameStr).arg(item.num+1).arg(str);
    ui->titleLab->setText(title);
}

void SetThresholdDlg::set(sThresholdItem &item)
{
    sBusData *busData = &(share_mem_get()->data[item.bus]);
    sObjData *obj = &(busData->box[item.box].data);

    sDataUnit  *unit = &(busData->box[item.box].env.tem);
    switch (item.type) {
    case 1: unit = &(obj->vol); break;
    case 2: unit = &(obj->cur); break;
    }
    item.min = unit->min[item.num];
    item.max = unit->max[item.num];

    mItem = item;
    setTitle(item);
    initSpinBox(item);
}


bool SetThresholdDlg::checkData()
{
    bool ret = true;
    int min = ui->minBox->value();
    int max = ui->maxBox->value();
    if(max < min)  {
        mItem.min = min;
        mItem.max = max;
    } else {
        QMessageBox::warning(this,tr("waring"),tr("最小值大于最大值！"),tr("OK"));
        ret = false;
    }

    return ret;
}


void SetThresholdDlg::on_saveBtn_clicked()
{
    bool ret = checkData();
    if(ret) {
        if(ui->checkBox->isChecked()) {
            if(mItem.box) mItem.box = 0xFF;
            else mItem.bus = 0xFf;
        }
    }
}

void SetThresholdDlg::on_cancelBtn_clicked()
{
    this->close();
}
