#ifndef E_INPUTUNITWID_H
#define E_INPUTUNITWID_H

#include "eload_rtu/eload_rtusent.h"
#include "in_com/in_datapackets.h"
#include <QWidget>

namespace Ui {
class E_InputUnitWid;
}

class E_InputUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit E_InputUnitWid(QWidget *parent = 0);
    ~E_InputUnitWid();

    void init(int addr, int bit);

protected:
    void updateWid();

private slots:
    void initFunSLot();
    void timeoutDone();
    void on_openBtn_clicked();

    void on_closeBtn_clicked();

    void on_checkBox_clicked(bool checked);

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::E_InputUnitWid *ui;

    QTimer *timer;
    sObjData *mObjData;
    ELoad_RtuSent *rtu;
    int mAddr, mBit;
};

#endif // E_INPUTUNITWID_H
