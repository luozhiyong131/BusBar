#ifndef LINEWID_H
#define LINEWID_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include "linetotalwid.h"
#include "lineroadwid.h"
#include "customdialplot.h"

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
    void initTotalWid();
    void onUpdateDials();

protected slots:
    void timeoutDone();

private slots:

private:
    Ui::LineWid *ui;
    QTimer *timer;
    LineTotalWid *mTotalWid;
    LineRoadWid *mLine[3];
    sBusData *mData;
    CustomDialPlot *mCurPlot;
    CustomDialPlot *mVolPlot;
    CustomDialPlot *mPwPlot;
    CustomDialPlot *mPfPlot;
};

#endif // LINEWID_H
