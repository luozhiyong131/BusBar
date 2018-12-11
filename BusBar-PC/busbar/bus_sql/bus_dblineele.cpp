/*
 * dbmainele.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "bus_dblineele.h"

BUS_DbLineEle::BUS_DbLineEle()
{

}

void BUS_DbLineEle::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "line_1        DOUBLE,"
            "line_2        DOUBLE,"
            "line_3        DOUBLE,"
            "line          DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool BUS_DbLineEle::insertItem(DbLineEleItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time,  line_1, line_2, line_3, line) "
            "values(:id,:date,:time,:line_1,:line_2,:line_3,:line)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BUS_DbLineEle::modifyItem(const DbLineEleItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":line_1",item.line_1);
    query.bindValue(":line_2",item.line_2);
    query.bindValue(":line_3",item.line_3);
    query.bindValue(":line",item.line);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BUS_DbLineEle::selectItem(QSqlQuery &query,DbLineEleItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.line_1 = query.value("line_1").toDouble();
    item.line_2 = query.value("line_2").toDouble();
    item.line_3 = query.value("line_3").toDouble();
    item.line = query.value("line").toDouble();
}

BUS_DbLineEle* bus_lineEle_db(int id)
{
    static DbLineEle1* sington1  = new DbLineEle1();
    static DbLineEle2* sington2  = new DbLineEle2();
    static DbLineEle3* sington3  = new DbLineEle3();
    static DbLineEle4* sington4  = new DbLineEle4();

    BUS_DbLineEle* sington = NULL;
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
