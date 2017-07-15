/*
 * dbbranchele.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "dbbranchele.h"

DbBranchEle::DbBranchEle()
{
    createTable();
}

void DbBranchEle::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "name           VCHAR,"
            "loop_1        DOUBLE,"
            "loop_2        DOUBLE,"
            "loop_3        DOUBLE,"
            "loop          DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool DbBranchEle::insertItem(DbBranchEleItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, name, loop_1, loop_2, loop_3, loop) "
            "values(:id,:date,:time,:name,:loop_1,:loop_2,:loop_3,:loop)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}


bool DbBranchEle::modifyItem(const DbBranchEleItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":name",item.name);
    query.bindValue(":loop_1",item.loop_1);
    query.bindValue(":loop_2",item.loop_2);
    query.bindValue(":loop_3",item.loop_3);
    query.bindValue(":loop",item.loop);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbBranchEle::selectItem(QSqlQuery &query,DbBranchEleItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.name = query.value("name").toString();
    item.loop_1 = query.value("loop_1").toDouble();
    item.loop_2 = query.value("loop_2").toDouble();
    item.loop_3 = query.value("loop_3").toDouble();
    item.loop = query.value("loop").toDouble();
}



DbBranchEle* db_branchEle_obj(int id)
{
    static DbBranchEle* sington1  = new DbBranchEle();
    static DbBranchEle2* sington2  = new DbBranchEle2();
    static DbBranchEle3* sington3  = new DbBranchEle3();
    static DbBranchEle4* sington4  = new DbBranchEle4();

    DbBranchEle* sington = NULL;
    switch (id)
    {
    case 0:
        sington = sington1;
        break;

    case 1:
        sington = sington2;
        break;

    case 2:
        sington = sington3;
        break;

    case 3:
        sington = sington4;
        break;
    }
    return sington;
}
