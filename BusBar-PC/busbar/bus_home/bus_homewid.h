#ifndef HOMEWID_H
#define HOMEWID_H

#include "bus_homeboxwid.h"

namespace Ui {
class BUS_HomeWid;
}

class BUS_HomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_HomeWid(QWidget *parent = 0);
    ~BUS_HomeWid();

protected:
    void initFun();
    void initWidget();
    bool checkBoxBaseNum();
    void setBoxBaseNum();

signals:
    void busChangedSig(int);

public slots:
    void timeoutDone();
    void busChangedSlot(int);
    void on_upBtn_clicked();
    void on_downBtn_clicked();

private:
    Ui::BUS_HomeWid *ui;
    QTimer *timer;

    int mBaseNum;
    sDevPackets *mBusData;
    BUS_HomeBoxWid *mBoxWid[10];
    int mMaxNum;
};

#endif // HOMEWID_H
