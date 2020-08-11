#include "checkpassworddlg.h"
#include "ui_checkpassworddlg.h"
//#include "frminput.h"

CheckPasswordDlg::CheckPasswordDlg(QWidget *parent,bool flag) :
    QDialog(parent),mSetOrLockWid(flag),
    ui(new Ui::CheckPasswordDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("身份验证"), this);

    mNumberKeyboard = new MyNumberKeyboardWid(ui->widget_2);
    QHBoxLayout *layout = new QHBoxLayout(ui->widget_2);
    layout->addWidget(mNumberKeyboard);
    mNumberKeyboard->setCurrentLineEdit(ui->lineEdit);
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

    if(mSetOrLockWid)
        emit dialogClosed(mResult);
    else
        emit dialogLockClosed(mResult);
    this->close();
}
