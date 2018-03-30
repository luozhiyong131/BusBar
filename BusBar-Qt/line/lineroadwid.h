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

   void initLine(int id);

protected:
    void updateData();
    void updateAlarmStatus(QLabel *lab, sDataUnit &unit);

public slots:
    void busChangeSlot(int id);

protected slots:
    void timeoutDone();
    void interfaceChangedSlot(int id);

private:
    Ui::LineRoadWid *ui;

    int mID;
    sObjData *mData;
    sEnvData *mEnv;
    QTimer *timer;
    //char mDc; //交只流  0为直流 其他交流
    int mBusId; //当前母线

    bool isRun;
};

#endif // LINEROADWID_H
