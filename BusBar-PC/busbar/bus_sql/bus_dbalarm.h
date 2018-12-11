#ifndef BUS_DBALARM_H
#define BUS_DBALARM_H

#include "basicsql.h"

#define BUS_TABLE_ALARM "bus_alarm"

struct BUS_DbAlarmItem : public DbBasicItem{
    QString type;
    QString msg;
};


class BUS_DbAlarm : public SqlBasic<BUS_DbAlarmItem>
{    
public:
    BUS_DbAlarm();
    bool insertItem(BUS_DbAlarmItem &item); // 插入

    void createTable();
     QString tableName(){return QString("%1_%2").arg(BUS_TABLE_ALARM).arg(mId) ;}
protected:
    bool modifyItem(const BUS_DbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BUS_DbAlarmItem &item);
    int mId;
};

class DbAlarm1 : public BUS_DbAlarm
{
public:
    DbAlarm1(){ mId=1; createTable(); }
};


class DbAlarm2 : public BUS_DbAlarm
{
public:
    DbAlarm2(){ mId=2; createTable(); }
};


class DbAlarm3 : public BUS_DbAlarm
{
public:
    DbAlarm3(){ mId=3; createTable(); }
};

class DbAlarm4 : public BUS_DbAlarm
{
public:
    DbAlarm4(){ mId=4; createTable(); }
};

BUS_DbAlarm* bus_alarm_db(int id);

#endif // DBALARM_H
