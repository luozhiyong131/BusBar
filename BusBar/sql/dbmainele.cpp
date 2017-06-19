#include "dbmainele.h"

DbMainEle::DbMainEle()
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


DbMainEle *DbMainEle::bulid()
{
    static DbMainEle* sington = NULL;
    if(sington == NULL)
        sington = new DbMainEle();
    return sington;
}

bool DbMainEle::insertItem(DbMainEleItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, line_1, line_2, line_3, line) "
            "values(:id,:date,:time,:line_1,:line_2,:line_3,:line)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}


bool DbMainEle::modifyItem(const DbMainEleItem &item, const QString &cmd)
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

void DbMainEle::selectItem(QSqlQuery &query,DbMainEleItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("name").toString();
    item.line_1 = query.value("line_1").toDouble();
    item.line_2 = query.value("line_2").toDouble();
    item.line_3 = query.value("line_3").toDouble();
    item.line = query.value("line").toDouble();
}
