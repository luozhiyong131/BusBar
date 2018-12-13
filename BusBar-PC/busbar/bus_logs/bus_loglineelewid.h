#ifndef BUS_LOGLINEELEWID_H
#define BUS_LOGLINEELEWID_H

#include "bus_logalarmwid.h"

class BUS_LogLineEleWid : public BUS_LogAlarmWid
{
    Q_OBJECT
public:
    explicit BUS_LogLineEleWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUS_LOGLINEELEWID_H
