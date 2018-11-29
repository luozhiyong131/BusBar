#ifndef THDMAINWID_H
#define THDMAINWID_H

#include "thdchartwid.h"
#include "thdtablewid.h"

namespace Ui {
class ThdMainWid;
}

class ThdMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ThdMainWid(QWidget *parent = 0);
    ~ThdMainWid();

private:
    Ui::ThdMainWid *ui;
    ThdChartWid *mChartWid;
    ThdTableWid *mTableWid;
};

#endif // THDMAINWID_H
