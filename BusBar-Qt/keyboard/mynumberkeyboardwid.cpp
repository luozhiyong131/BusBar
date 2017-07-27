#include "mynumberkeyboardwid.h"
#include "ui_mynumberkeyboardwid.h"

MyNumberKeyboardWid::MyNumberKeyboardWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyNumberKeyboardWid)
{
    ui->setupUi(this);

    initWid();
}

MyNumberKeyboardWid::~MyNumberKeyboardWid()
{
    delete ui;
}

void MyNumberKeyboardWid::initWid()
{
    qDebug() << "------initwid------";
    initButton();
    int i = 0;

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        qDebug() << "---i---" << i++;
        connect(b, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }
}

void MyNumberKeyboardWid::initButton()
{
    qDebug() << "------initbutton------";

    ui->pushButton_0->setProperty("number",true);
    ui->pushButton_1->setProperty("number",true);
    ui->pushButton_2->setProperty("number",true);
    ui->pushButton_3->setProperty("number",true);
    ui->pushButton_4->setProperty("number",true);
    ui->pushButton_5->setProperty("number",true);
    ui->pushButton_6->setProperty("number",true);
    ui->pushButton_7->setProperty("number",true);
    ui->pushButton_8->setProperty("number",true);
    ui->pushButton_9->setProperty("number",true);
    ui->pushButton_space->setProperty("nonnumber",true);
    ui->pushButton_delate->setProperty("nonnumber",true);
}

void MyNumberKeyboardWid::buttonClicked()
{
    //    qDebug() << "numberclicked";

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    QString text = btn->text();
    bool isnum = btn->property("number").toBool();

    qDebug() << "numberclicked"<< text << objectName;

    if(isnum)
    {
        qDebug() << "==============================number";
        insertValue(text);
    }else if(text == "delate")
    {
        qDebug() << "==============================delate";
        delateValue();

    }
    else if(text == "space")
        insertSpace();
}

void MyNumberKeyboardWid::insertValue(QString text)
{
    qDebug() << "===text===" << text;
    mEdit->insert(text);
}

void MyNumberKeyboardWid::delateValue()
{
    qDebug() << "delatevalue";
    QString text = mEdit->text();
    QString newText ="";
    int len = text.length();
    if(len >1)
        newText = text.remove(len-1,1);
    mEdit->clear();
    mEdit->setText(newText);
    qDebug() << "delatevalue"<< newText;
}

void MyNumberKeyboardWid::insertSpace()
{

}

void MyNumberKeyboardWid::setCurrentLineEdit(QLineEdit *lineedit)
{
    mEdit = lineedit;
}

