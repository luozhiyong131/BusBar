#include "dbbranchele.h"

DbBranchEle::DbBranchEle()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "output_1        DOUBLE,"
            "output_2        DOUBLE,"
            "output_3        DOUBLE,"
            "output          DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


DbBranchEle *DbBranchEle::bulid()
{
    static DbBranchEle* sington = NULL;
    if(sington == NULL)
        sington = new DbBranchEle();
    return sington;
}

bool DbBranchEle::insertItem(DbBranchEleItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, output_1, output_2, output_3, output) "
            "values(:id,:date,:time,:output_1,:output_2,:output_3,:output)";
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
    query.bindValue(":output_1",item.output_1);
    query.bindValue(":output_2",item.output_2);
    query.bindValue(":output_3",item.output_3);
    query.bindValue(":output",item.output);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbBranchEle::selectItem(QSqlQuery &query,DbBranchEleItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("name").toString();
    item.output_1 = query.value("output_1").toDouble();
    item.output_2 = query.value("output_2").toDouble();
    item.output_3 = query.value("output_3").toDouble();
    item.output = query.value("output").toDouble();
}
