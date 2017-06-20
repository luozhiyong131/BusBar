/*
 * dbthreshold.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "dbthreshold.h"

DbThreshold::DbThreshold()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "bus            INTEGER,"
            "type           INTEGER,"
            "num          INTEGER,"
            "min          INTEGER,"
            "crmin        INTEGER,"
            "crmax        INTEGER,"
            "max          INTEGER);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}



DbThreshold *DbThreshold::bulid()
{
    static DbThreshold* sington = NULL;
    if(sington == NULL)
        sington = new DbThreshold();
    return sington;
}

bool DbThreshold::insertItem(DbThresholdItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, bus, type, num, min, crmin, crmax, max) "
                  "values(:id,:bus,:type,:num,:min,:crmin,:crmax,:max)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}


bool DbThreshold::updateItem(const DbThresholdItem &item)
{
    bool ret = false;
    QString cmd = "update %1 set "
                  "bus       = :bus,"
                  "type      = :type,"
                  "num       = :num,"
                  "min       = :min,"
                  "crmin     = :crmin,"
                  "crmax     = :crmax,"
                  "max         = :max"
                  " where id   = :id";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool DbThreshold::modifyItem(const DbThresholdItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":bus",item.bus);
    query.bindValue(":type",item.type);
    query.bindValue(":num",item.num);
    query.bindValue(":min",item.min);
    query.bindValue(":crmin",item.crmin);
    query.bindValue(":crmax",item.crmax);
    query.bindValue(":max",item.max);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbThreshold::selectItem(QSqlQuery &query,DbThresholdItem &item)
{
    item.id = query.value("id").toInt();
    item.bus = query.value("bus").toInt();
    item.type = query.value("type").toInt();
    item.num = query.value("num").toInt();
    item.min = query.value("min").toInt();
    item.crmin = query.value("crmin").toInt();
    item.crmax = query.value("crmax").toInt();
    item.max = query.value("max").toInt();
}

int DbThreshold::getId(DbThresholdItem &item)
{
    QString condition = QString("where bus=%1 and type=%2 and num=%3").arg(item.bus).arg(item.type).arg(item.num);
    return  maxId("id", condition);
}

bool DbThreshold::saveItem(DbThresholdItem &item)
{
    bool ret=false;
    int id = getId(item);
    if(id > 0) {
        item.id = id;
        ret = updateItem(item);
    } else
        ret = insertItem(item);
    return ret;
}

void  DbThreshold::updateThreshold(DbThresholdItem &item, const QString &cmd)
{
    updateColumn("min", item.min, cmd);
    updateColumn("crmin", item.crmin, cmd);
    updateColumn("crmax", item.crmax, cmd);
    updateColumn("max", item.max, cmd);
}

void DbThreshold::unifiedSet(DbThresholdItem &item)
{
    QString condition = QString("where bus=%1 and type=%2").arg(item.bus).arg(item.type);
    updateThreshold(item, condition);
}

void DbThreshold::globalSet(DbThresholdItem &item)
{
    QString condition = QString("where type=%1 and num=%2").arg(item.type).arg(item.num);
    updateThreshold(item, condition);
}

void DbThreshold::globalUnifiedSet(DbThresholdItem &item)
{
    QString condition = QString("where type=%1").arg(item.type);
    updateThreshold(item, condition);
}
