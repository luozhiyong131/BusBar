#include "checkpassworddlg.h"
#include "ui_checkpassworddlg.h"
//#include "frminput.h"

CheckPasswordDlg::CheckPasswordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPasswordDlg)
{
    ui->setupUi(this);

//    frmInput::Instance()->Init("bottom", "black", 10, 10);  //打开中文输入法
}

CheckPasswordDlg::~CheckPasswordDlg()
{
    delete ui;
}

void CheckPasswordDlg::clear()
{
    ui->lineEdit->clear();
}

void CheckPasswordDlg::on_pushButton_clicked()
{
    QString str = getPassword();
    QString linestr = ui->lineEdit->text();
    if(str == linestr)
        mResult = true;
    else
        mResult = false;

    emit dialogClosed(mResult);
    this->close();
}
