/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dbenv.h"

DbEnv::DbEnv()
{
}

void DbEnv::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
            "sensor_id      INTEGER,"
            "tem            INTEGER,"
            "tem_min        INTEGER,"
            "tem_max        INTEGER,"
            "hum            INTEGER,"
            "hum_min        INTEGER,"
            "hum_max        INTEGER);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool DbEnv::insertItem(DbEnvItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, sensor_id, tem, tem_min, tem_max, hum, hum_min, hum_max) "
                  "values(:id,:date,:time,:dev_id,:sensor_id,:tem,:tem_min,:tem_max,:hum,:hum_min,:hum_max)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool DbEnv::modifyItem(const DbEnvItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":sensor_id",item.sensor_id);
    query.bindValue(":tem",item.tem);
    query.bindValue(":tem_min",item.tem_min);
    query.bindValue(":tem_max",item.tem_max);
    query.bindValue(":hum",item.hum);
    query.bindValue(":hum_min",item.hum_min);
    query.bindValue(":hum_max",item.hum_max);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbEnv::selectItem(QSqlQuery &query, DbEnvItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.sensor_id = query.value("sensor_id").toInt();
    item.tem = query.value("tem").toInt();
    item.tem_min = query.value("tem_min").toInt();
    item.tem_max = query.value("tem_max").toInt();
    item.hum = query.value("hum").toInt();
    item.hum_min = query.value("hum_min").toInt();
    item.hum_max = query.value("hum_max").toInt();
}

