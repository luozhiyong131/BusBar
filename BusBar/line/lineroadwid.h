#ifndef LINEROADWID_H
#define LINEROADWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class LineRoadWid;
}

class LineRoadWid : public QWidget
{
    Q_OBJECT

public:
    explicit LineRoadWid(QWidget *parent = 0);
    ~LineRoadWid();

protected:
    void updateData();
    void updateAlarmStatus(QLabel *lab, sDataUnit &unit);

public slots:
    void busChangeSlot(int id);

protected slots:
    void timeoutDone();

private:
    Ui::LineRoadWid *ui;

    int mID;
    sObjData *mData;
    QTimer *timer;
};

#endif // LINEROADWID_H
