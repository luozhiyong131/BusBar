#ifndef LINEWID_H
#define LINEWID_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include "linetotalwid.h"
#include "lineroadwid.h"
#include "customdialplot.h"
#include "setparameters/settingwid.h"
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
    void lockStatus(bool ret);

protected:
    void initFun();
    void initWid();
    void initTotalWid();
    void updateTotalWid();
    void updatePlot();

protected slots:
    void timeoutDone();
    void indexChanged(int index);
    void interfaceChangedSlot(int id);
    void dialogLockClosed(bool ret);

private slots:
    void on_lockBtn_clicked();

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
    int mIndex;
    bool isRun;
    CheckPasswordDlg *mCheckDlg;
    bool mLock;
};

#endif // LINEWID_H
