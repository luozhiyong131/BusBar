#ifndef HOMEBOXWID_H
#define HOMEBOXWID_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include "common.h"

namespace Ui {
class HomeBoxWid;
}

class HomeBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit HomeBoxWid(QWidget *parent = 0);
    ~HomeBoxWid();

    void initFun(int base, int id);
    void setBaseNum(int base);

protected:
    void updateData();
    void updateAlarmStatus();
    void updateAlarmIcon(QLabel *lab, sDataUnit &unit, int id);

    void initWid();

public slots:
    void busChangeSlot(int id);

private slots:
    void timeoutDone();
    void on_pushButton_clicked();

private:
    Ui::HomeBoxWid *ui;

    int mID, mBusID, mBaseNum;
    sBoxData *mData;
    QTimer *timer;
};

#endif // HOMEBOXWID_H
