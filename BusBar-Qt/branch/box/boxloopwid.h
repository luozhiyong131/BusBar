#ifndef BOXLOOPWID_H
#define BOXLOOPWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class BoxLoopWid;
}

class BoxLoopWid : public QWidget
{
    Q_OBJECT

public:
    explicit BoxLoopWid(QWidget *parent = 0);
    ~BoxLoopWid();

    void initLine(int bus, int box, int id);

protected:
    void updateData();
    void updateAlarmStatus(QLabel *lab, sDataUnit &unit);

protected slots:
    void timeoutDone();

private:
    Ui::BoxLoopWid *ui;

    int mID;
    sObjData *mData;
    sEnvData *mEnvData;
    QTimer *timer;
};

#endif // BOXLOOPWID_H
