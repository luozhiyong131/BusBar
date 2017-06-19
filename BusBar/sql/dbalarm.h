#ifndef DBALARM_H
#define DBALARM_H

#include "basicsql.h"

#define DB_TABLE_ALARM "alarm"

struct DbAlarmItem : public DbBasicItem{
    QString msg;
};


class DbAlarm : public SqlBasic<DbAlarmItem>
{    
public:
    DbAlarm();
    static DbAlarm* bulid();
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_ALARM).arg(1) ;}
    bool insertItem(DbAlarmItem &item); // 插入

protected:
    bool modifyItem(const DbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbAlarmItem &item);
};




class DbAlarm2 : public DbAlarm
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_ALARM).arg(2) ;}
};


class DbAlarm3 : public DbAlarm
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_ALARM).arg(3) ;}
};

class DbAlarm4 : public DbAlarm
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_ALARM).arg(4) ;}
};

#endif // DBALARM_H
