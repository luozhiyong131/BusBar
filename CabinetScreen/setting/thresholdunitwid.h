#ifndef THRESHOLDUNITWID_H
#define THRESHOLDUNITWID_H

#include <QWidget>
#include "inputdlg.h"


namespace Ui {
class ThresholdUnitWid;
}

class ThresholdUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ThresholdUnitWid(QWidget *parent = 0);
    ~ThresholdUnitWid();

    void init(int id, int mode, int line);
    void setLine(int line) {mLine=line;}

protected:
    void initWid();
    void updateDataUnit();
    void checkAlarm();

protected slots:
    void timeoutDone();

private slots:
    void on_setBtn_clicked();

private:
    Ui::ThresholdUnitWid *ui;

    QTimer *timer;
    QString mStr;
    double mRate;
    sDataUnit *mDataUnit;
    sDevData *mDev;
    int mDevId, mMode, mLine;
};

#endif // THRESHOLDUNITWID_H
