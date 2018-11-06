#ifndef SETLINEWID_H
#define SETLINEWID_H

#include "setlineitem.h"

namespace Ui {
class SetLineWid;
}

class SetLineWid : public QWidget
{
    Q_OBJECT

public:
    explicit SetLineWid(QWidget *parent = 0);
    ~SetLineWid();

private:
    Ui::SetLineWid *ui;
    SetLineItem *mItem[3];
};

#endif // SETLINEWID_H
