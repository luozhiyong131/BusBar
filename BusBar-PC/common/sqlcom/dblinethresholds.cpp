/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dblinethresholds.h"

DbLineThresholds::DbLineThresholds()
{
}

void DbLineThresholds::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
            "line           INTEGER,"
            "vol            DOUBLE,"
            "vol_min        DOUBLE,"
            "vol_max        DOUBLE,"
            "cur            DOUBLE,"
            "cur_min        DOUBLE,"
            "cur_max        DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool DbLineThresholds::insertItem(DbLineThresholdItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, line,vol, vol_min, vol_max, cur, cur_min, cur_max) "
                  "values(:id,:date,:time,:dev_id,:line,:vol,:vol_min,:vol_max,:cur,:cur_min,:cur_max)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool DbLineThresholds::modifyItem(const DbLineThresholdItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":line",item.line);
    query.bindValue(":vol",item.vol);
    query.bindValue(":vol_min",item.vol_min);
    query.bindValue(":vol_max",item.vol_max);
    query.bindValue(":cur",item.cur);
    query.bindValue(":cur_min",item.cur_min);
    query.bindValue(":cur_max",item.cur_max);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbLineThresholds::selectItem(QSqlQuery &query, DbLineThresholdItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.line = query.value("line").toInt();
    item.vol = query.value("vol").toDouble();
    item.vol_min = query.value("vol_min").toDouble();
    item.vol_max = query.value("vol_max").toDouble();
    item.cur = query.value("cur").toDouble();
    item.cur_min = query.value("cur_min").toDouble();
    item.cur_max = query.value("cur_max").toDouble();
}
