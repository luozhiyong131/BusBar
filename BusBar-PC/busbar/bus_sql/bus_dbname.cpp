#include "bus_dbname.h"

BUS_DbName::BUS_DbName()
{
    createTable();
}

void BUS_DbName::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "bus            INTEGER,"
            "type           INTEGER,"
            "box          INTEGER,"
            "num          INTEGER,"
            "name          TEXT);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


BUS_DbName *BUS_DbName::bulid()
{
    static BUS_DbName* sington = NULL;
    if(sington == NULL)
        sington = new BUS_DbName();
    return sington;
}

bool BUS_DbName::insertItem(DbNameItem& item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, bus, type, box, num, name) "
                  "values(:id,:bus,:type,:box,:num,:name)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}


bool BUS_DbName::updateItem(const DbNameItem &item)
{
    bool ret = false;
    QString cmd = "update %1 set "
                  "bus       = :bus,"
                  "type      = :type,"
                  "box       = :box,"
                  "num       = :num,"
                  "name      = :name"
                  " where id   = :id";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool BUS_DbName::modifyItem(const DbNameItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":bus",item.bus);
    query.bindValue(":type",item.type);
    query.bindValue(":box",item.box);
    query.bindValue(":num",item.num);
    query.bindValue(":name",item.name);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BUS_DbName::selectItem(QSqlQuery &query,DbNameItem &item)
{
    item.id = query.value("id").toInt();
    item.bus = query.value("bus").toInt();
    item.type = query.value("type").toInt();
    item.box = query.value("box").toInt();
    item.num = query.value("num").toInt();
    item.name = query.value("name").toString();
}

int BUS_DbName::getId(DbNameItem &item)
{
    QString condition = QString("where bus=%1 and type=%2 and box=%3 and num=%4")
            .arg(item.bus).arg(item.type).arg(item.box).arg(item.num);
    return  maxId("id", condition);
}


bool BUS_DbName::saveItem(DbNameItem &item)
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

bool BUS_DbName::setName(int busId, int typeId, int num, const QString &name)
{
    DbNameItem item;
    item.bus = busId;
    item.type = typeId;
    item.num = num;
    item.name = name;

    return saveItem(item);
}

QString BUS_DbName::getName(int busId, int typeId, int num)
{
    DbNameItem item;
    item.bus = busId;
    item.type = typeId;
    item.num = num;

    int id = getId(item);
    if(id > 0) {
        item.name = findById(id).name;
    }

    return item.name;
}
