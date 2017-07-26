#include "passordsettingdlg.h"
#include "ui_passordsettingdlg.h"

PassordSettingDlg::PassordSettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassordSettingDlg)
{
    ui->setupUi(this);
    //    sys_configFile_writeParam("password","admin");

    //    QString password = getPassword();
    //    qDebug() << "---password---" << password;
}

PassordSettingDlg::~PassordSettingDlg()
{
    delete ui;
}

void PassordSettingDlg::on_pushButton_2_clicked()
{
    this->close();
}
