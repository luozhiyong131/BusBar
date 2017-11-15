#ifndef DEVTHRESHOLDWID_H
#define DEVTHRESHOLDWID_H

#include <QWidget>
#include "common.h"
#include "thresholdunitwid.h"

namespace Ui {
class DevThresholdWid;
}

class DevThresholdWid : public QWidget
{
    Q_OBJECT

public:
    explicit DevThresholdWid(QWidget *parent = 0);
    ~DevThresholdWid();

    void init(int id);


private:
    Ui::DevThresholdWid *ui;

    int mLine;
    ThresholdUnitWid *mUnitWid[4];
};

#endif // DEVTHRESHOLDWID_H
