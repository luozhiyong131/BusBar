#ifndef THDMAINDLG_H
#define THDMAINDLG_H

#include <QDialog>
#include "bus_thdchartwid.h"
#include "bus_thdtablewid.h"

namespace Ui {
class BUS_ThdMainDlg;
}

class BUS_ThdMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BUS_ThdMainDlg(QWidget *parent = 0);
    ~BUS_ThdMainDlg();

    void initBus(int id);

protected:
    void setLine(int i, int l);

private slots:
    void timeoutDone();
    void on_volAbtn_clicked();
    void on_volBbtn_clicked();
    void on_volCbtn_clicked();
    void on_curAbtn_clicked();
    void on_curBbtn_clicked();
    void on_curCbtn_clicked();
    void on_quitBtn_clicked();

private:
    Ui::BUS_ThdMainDlg *ui;
    QTimer *timer;
    ushort *mThd, *mLineThd;
    sDevPackets *mBusData;

    BUS_ThdChartWid *mChartWid;
    ThdTableWid *mTableWid;
};

#endif // THDMAINDLG_H
