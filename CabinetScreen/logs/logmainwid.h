#ifndef LOGMAINWID_H
#define LOGMAINWID_H

#include "logalarm/logalarmwid.h"
#include "logcab/logcabelewid.h"
#include "logdev/logdevwid.h"

namespace Ui {
class LogMainWid;
}

class LogMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogMainWid(QWidget *parent = 0);
    ~LogMainWid();

protected:
    void initWidget();

private slots:
    void logTypeSlot(int);

private:
    Ui::LogMainWid *ui;

    LogCabEleWid *mCabEleWid;
    LogDevWid *mDevWid;
    LogAlarmWid *mAlarmWid;
};

#endif // LOGMAINWID_H
