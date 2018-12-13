#ifndef BUS_LOGALARMWID_H
#define BUS_LOGALARMWID_H

#include "logcomwid.h"
#include "bus_sql/bus_dblineele.h"

class BUS_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BUS_LogAlarmWid(QWidget *parent = nullptr);

public slots:
    void setTableSlot(int id);

protected:
    void initTable();
    BasicSql *getDb();

protected:
    int mId;
};

#endif // BUS_LOGALARMWID_H
