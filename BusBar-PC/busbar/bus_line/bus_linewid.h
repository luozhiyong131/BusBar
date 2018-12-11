#ifndef LINEWID_H
#define LINEWID_H

#include <QHBoxLayout>
#include "bus_linetablewid.h"


namespace Ui {
class BUS_LineWid;
}

class BUS_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_LineWid(QWidget *parent = 0);
    ~BUS_LineWid();

signals:
    void busChangedSig(int);


protected slots:
    void timeoutDone();
    void indexChanged(int index);

private slots:
    void on_thdBtn_clicked();

private:
    Ui::BUS_LineWid *ui;

    QTimer *timer;
    BUS_LineTableWid *mLineTable;
    sDataPacket *mDev;

    int mIndex;
};

#endif // LINEWID_H
