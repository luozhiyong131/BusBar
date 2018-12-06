/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dblinerecords.h"

DbLineRecords::DbLineRecords()
{
}

void DbLineRecords::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
            "line           INTEGER,"
            "sw             INTEGER,"
            "sw_str         VCHAR,"
            "vol            DOUBLE,"
            "cur            DOUBLE,"
            "pow            DOUBLE,"
            "apow           DOUBLE,"
            "pf             DOUBLE,"
            "ele            DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool DbLineRecords::insertItem(DbLineRecordItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, line, sw, sw_str, vol, cur, pow, apow, pf, ele) "
                  "values(:id,:date,:time,:dev_id,:line,:sw,:sw_str,:vol,:cur,:pow,:apow,:pf,:ele)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool DbLineRecords::modifyItem(const DbLineRecordItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":line",item.line);
    query.bindValue(":sw",item.sw);
    query.bindValue(":sw_str",item.sw_str);
    query.bindValue(":vol",item.vol);
    query.bindValue(":cur",item.cur);
    query.bindValue(":pow",item.pow);
    query.bindValue(":apow",item.apow);
    query.bindValue(":pf",item.pf);
    query.bindValue(":ele",item.ele);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbLineRecords::selectItem(QSqlQuery &query, DbLineRecordItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.line = query.value("line").toInt();
    item.sw = query.value("sw").toInt();
    item.sw_str = query.value("sw_str").toString();
    item.vol = query.value("vol").toDouble();
    item.cur = query.value("cur").toDouble();
    item.pow = query.value("pow").toDouble();
    item.apow = query.value("apow").toDouble();
    item.pf = query.value("pf").toDouble();
    item.ele = query.value("ele").toDouble();
}

