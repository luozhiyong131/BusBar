#ifndef SETMAINWID_H
#define SETMAINWID_H

#include "devthresholdwid.h"

namespace Ui {
class SetMainWid;
}

class SetMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SetMainWid(QWidget *parent = 0);
    ~SetMainWid();

private:
    Ui::SetMainWid *ui;
    DevThresholdWid *mDevWid[DEV_NUM];
};

#endif // SETMAINWID_H
