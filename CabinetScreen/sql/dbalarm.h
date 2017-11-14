#ifndef DBALARM_H
#define DBALARM_H

#include "basicsql.h"

#define DB_TABLE_ALARM "alarm"

struct DbAlarmItem : public DbBasicItem{
    QString type;
    QString msg;
};


class DbAlarm : public SqlBasic<DbAlarmItem>
{    
    DbAlarm();
public:
    static DbAlarm *bulid();
    QString tableName(){return QString("%1").arg(DB_TABLE_ALARM);}
    bool insertItem(DbAlarmItem &item); // 插入

protected:
    void createTable();
    bool modifyItem(const DbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbAlarmItem &item);
};

#endif // DBALARM_H
