#ifndef LOGALARMWID_H
#define LOGALARMWID_H

#include "logcom/logcomelewid.h"

class LogAlarmWid : public LogComEleWid
{
    Q_OBJECT
public:
    explicit LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    QString getTableName();

protected slots:
    virtual void clearTableSlot();
};

#endif // LOGALARMWID_H
