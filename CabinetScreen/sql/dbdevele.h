#ifndef DBBRANCHELE_H
#define DBBRANCHELE_H

#include "dbcabele.h"

#define DB_TABLE_DEVELE "dev_ele"

struct DbDevEleItem : public DbCabEleItem{
    QString name;
};


class DbDevEle : public SqlBasic<DbDevEleItem>
{
public:
    DbDevEle();

    QString tableName(){return QString("%1").arg(DB_TABLE_DEVELE) ;}
    bool insertItem(DbDevEleItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const DbDevEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbDevEleItem &item);
};


#endif // DBBRANCHELE_H
