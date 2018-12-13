#ifndef HOMEBOXWID_H
#define HOMEBOXWID_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include "bus_box/bus_boxdlg.h"

namespace Ui {
class BUS_HomeBoxWid;
}

class BUS_HomeBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_HomeBoxWid(QWidget *parent = 0);
    ~BUS_HomeBoxWid();

    void initFun(int base, int id);
    void setBaseNum(int base);
protected:
    void updateData();
    void updateAlarmStatus();
    void updateAlarmIcon(QLabel *lab);
    void initWid();
    void setBackgroundImage(QLabel *lab,QString name);

public slots:
    void busChangeSlot(int id);

private slots:
    void timeoutDone();
    void on_pushButton_clicked();

private:
    Ui::BUS_HomeBoxWid *ui;

    int mBoxNum;
    int mID, mBusID, mBaseNum;
    sDataPacket *mData;
    QTimer *timer;
};

#endif // HOMEBOXWID_H
