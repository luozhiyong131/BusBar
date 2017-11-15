#ifndef THRESHOLDUNITWID_H
#define THRESHOLDUNITWID_H

#include <QWidget>
#include "common.h"

enum {
    VolMode,
    CurMode,
    TemMode,
    HumMode,
};

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

protected:
    void initWid();
    void updateDataUnit();
    void checkAlarm();

protected slots:
    void timeoutDone();

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
