#ifndef HOMEBOXWID_H
#define HOMEBOXWID_H

#include <QWidget>
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

    void initFun(int id);

protected:
    void updateData();
    void updateAlarmStatus(QLabel *lab, sDataUnit &unit);

public slots:
    void busChangeSlot(int id);

private slots:
    void timeoutDone();
    void on_pushButton_clicked();

private:
    Ui::HomeBoxWid *ui;

    int mID;
    sBoxData *mData;
    QTimer *timer;
};

#endif // HOMEBOXWID_H
