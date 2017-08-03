#ifndef MYNUMBERKEYBOARDWID_H
#define MYNUMBERKEYBOARDWID_H

#include <QWidget>
#include <QLineEdit>
#include <QDebug>

namespace Ui {
class MyNumberKeyboardWid;
}

class MyNumberKeyboardWid : public QWidget
{
    Q_OBJECT

public:
    explicit MyNumberKeyboardWid(QWidget *parent = 0);
    ~MyNumberKeyboardWid();

    void setCurrentLineEdit(QLineEdit *lineedit);

private slots:
    void buttonClicked();

private:
    void initWid();
    void initButton();
    void insertValue(QString text);
    void delateValue();
    void insertSpace();

private:
    Ui::MyNumberKeyboardWid *ui;
    QLineEdit *mEdit;
};

#endif // MYNUMBERKEYBOARDWID_H
