#ifndef LOGSWID_H
#define LOGSWID_H

#include <QWidget>
#include "bus_logbranchelewid.h"

namespace Ui {
class BUS_LogsWid;
}

class BUS_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_LogsWid(QWidget *parent = 0);
    ~BUS_LogsWid();

protected:
    void initWidget();

signals:
    void busChangedSig(int);

private slots:
    void logTypeSlot(int);
    void on_lineBtn_clicked();
    void on_loopBtn_clicked();
    void on_alarmBtn_clicked();

private:
    Ui::BUS_LogsWid *ui;

    BUS_LogLineEleWid *mMainEleWid;
    BUS_LogBranchEleWid *mBranchEleWid;
    BUS_LogAlarmWid *mAlarmWid;
};

#endif // LOGSWID_H
