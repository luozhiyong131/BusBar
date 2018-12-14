#include "setnamedlg.h"
#include "ui_setnamedlg.h"


SetNameDlg::SetNameDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNameDlg)
{
    ui->setupUi(this);
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
    int type=2;
    BUS_SetShm shm;

    DbNameItem item;
    item.bus = mBusId;
    item.box = mBox;

    if(mLoop) {
        type = 3;
    }

    item.type = type;
    item.num = mLoop;
    item.name = ui->nameEdit->text();
    shm.setName(item);

    return true;
}

void SetNameDlg::on_saveBtn_clicked()
{
    QString str = ui->nameEdit->text();
    if(!str.isEmpty()) {
        if(save())
        {
            close();
        }
    } else {
        CriticalMsgBox box(this, tr("名称不能为空!!"));
    }
}

void SetNameDlg::on_cancelBtn_clicked()
{
    close();
}
