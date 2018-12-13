#ifndef BUS_DBDEVNAME_H
#define BUS_DBDEVNAME_H

#include "bus_dbbranchele.h"

#define DB_TABLE_DEVNAME "bus_name"

struct DbNameItem{
    DbNameItem() {box=num=0;}
    int id;
    int bus; // 母线编号 0~3
    int type; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    int box;
    int num; // 编号
    QString name;
};

class BUS_DbName : public SqlBasic<DbNameItem>
{
    BUS_DbName();
public:
    static BUS_DbName* bulid();
    bool saveItem(DbNameItem &item);
    QString getName(DbNameItem &item);

protected:
    void createTable();
    bool insertItem(DbNameItem &item); // 插入
    bool updateItem(const DbNameItem &item);

    bool modifyItem(const DbNameItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbNameItem &item);

    int getId(DbNameItem &item);
    QString tableName(){return QString("%1").arg(DB_TABLE_DEVNAME);}
};

#endif // DBDEVNAME_H
