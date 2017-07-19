#ifndef LINEWID_H
#define LINEWID_H

#include <QWidget>
#include "linetotalwid.h"
#include "lineroadwid.h"

namespace Ui {
class LineWid;
}

class LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit LineWid(QWidget *parent = 0);
    ~LineWid();

signals:
    void busChangedSig(int);

protected:
    void initFun();
    void initWid();

protected slots:
    void timeoutDone();

private slots:

private:
    Ui::LineWid *ui;
    QTimer *timer;
    LineTotalWid *mTotalWid;
    LineRoadWid *mLine[3];
    sBusData *mData;
};

#endif // LINEWID_H
