#ifndef DBALARM_H
#define DBALARM_H

#include "basicsql.h"

struct DbBasicItem{
    DbBasicItem():id(-1){
        QDateTime dateTime = QDateTime::currentDateTime();
        date = dateTime.toString("yyyy-MM-dd");
        time = dateTime.toString("hh:mm:ss");
    }

    int id;
    QString date, time;
};

struct DbAlarmItem : public DbBasicItem{

    QString msg;

};


class DbAlarm : public SqlBasic<DbAlarmItem>
{
    DbAlarm();
public:
    static DbAlarm* bulid();
    QString tableName(){return QString("%1").arg("alarm") ;}
    bool insertItem(DbAlarmItem &item); // 插入

protected:
    bool modifyItem(const DbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbAlarmItem &item);
};

#endif // DBALARM_H
