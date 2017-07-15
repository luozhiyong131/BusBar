#ifndef LOGSWID_H
#define LOGSWID_H

#include <QWidget>
#include "logmain/logmainelewid.h"
#include "logbranch/logbranchelewid.h"
#include "logalarm/logalarmwid.h"

namespace Ui {
class LogsWid;
}

class LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogsWid(QWidget *parent = 0);
    ~LogsWid();

protected:
    void initWidget();

private slots:
    void on_lineBtn_clicked();

    void on_branchBtn_clicked();

    void on_alarmBtn_clicked();

private:
    Ui::LogsWid *ui;

    LogMainEleWid *mMainEleWid;
    LogBranchEleWid *mBranchEleWid;
    LogAlarmWid *mAlarmWid;
};

#endif // LOGSWID_H
