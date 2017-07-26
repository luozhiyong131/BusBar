#include "checkpassworddlg.h"
#include "ui_checkpassworddlg.h"

CheckPasswordDlg::CheckPasswordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPasswordDlg)
{
    ui->setupUi(this);
}

CheckPasswordDlg::~CheckPasswordDlg()
{
    delete ui;
}

void CheckPasswordDlg::accept()
{
    QString str = getPassword();
    QString linestr = ui->lineEdit->text();
    qDebug() << str << ui->lineEdit->text();

    if((!linestr.isEmpty()) && (str == linestr))
        mResult = true;
    else
        mResult = false;

//    this->close();
}

bool CheckPasswordDlg::getResult()
{
    return mResult;
}
