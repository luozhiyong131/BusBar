#ifndef DBALARM_H
#define DBALARM_H
#include "basicsql.h"

struct DbAlarmItem : public DbBasicItem {
    int dev_id, line;
    QString type_str,msg;
};

class DbAlarm : public SqlBasic<DbAlarmItem>
{
public:
    DbAlarm();

    bool insertItem(DbAlarmItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbAlarmItem &item);
};

#endif // DBALARM_H
