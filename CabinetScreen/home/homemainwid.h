#ifndef HOMEMAINWID_H
#define HOMEMAINWID_H

#include <QWidget>
#include "pdudevwid.h"

namespace Ui {
class HomeMainWid;
}

class HomeMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit HomeMainWid(QWidget *parent = 0);
    ~HomeMainWid();

private:
    Ui::HomeMainWid *ui;

    PduDevWid *mDevWid[2];
};

#endif // HOMEMAINWID_H
