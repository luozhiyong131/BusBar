#include "setnamedlg.h"
#include "ui_setnamedlg.h"
#include "common.h"
#include "setshm.h"

SetNameDlg::SetNameDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNameDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("设置界面"), this);
}

SetNameDlg::~SetNameDlg()
{
    delete ui;
}

void SetNameDlg::init(int bus, int box, int loop, const QString &name)
{
    mBusId = bus;
    mBox = box;
    mLoop = loop;
    ui->nameLab->setText(name);
}

bool SetNameDlg::save()
{
    int type=2, num = mBox;
    SetShm shm;

    DbNameItem item;
    item.bus = mBusId;
    if(mLoop) {
        type = 3;
        num = (mBox-1)*LINE_NUM + mLoop-1 ;
    }

    item.type = type;
    item.num = num;
    item.name = ui->nameEdit->text();
    shm.setName(item);

    return true;
}

void SetNameDlg::on_saveBtn_clicked()
{
    QString str = ui->nameEdit->text();
    if(!str.isEmpty()) {
        if(save()) close();
    } else {
        CriticalMsgBox box(this, tr("名称不能为空!!"));
    }
}
