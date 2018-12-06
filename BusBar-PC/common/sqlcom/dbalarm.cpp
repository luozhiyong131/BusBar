/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dbalarm.h"

DbAlarm::DbAlarm()
{
}

void DbAlarm::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
            "line           INTEGER,"
            "type_str       VCHAR,"
            "msg            VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool DbAlarm::insertItem(DbAlarmItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, line, type_str, msg) "
                  "values(:id,:date,:time,:dev_id,:line,:type_str,:msg)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool DbAlarm::modifyItem(const DbAlarmItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":line",item.line);
    query.bindValue(":type_str",item.type_str);
    query.bindValue(":msg",item.msg);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbAlarm::selectItem(QSqlQuery &query, DbAlarmItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.line = query.value("line").toInt();
    item.type_str = query.value("type_str").toString();
    item.msg = query.value("msg").toString();
}

