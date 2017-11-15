#ifndef DBMAINELE_H
#define DBMAINELE_H

#include "basicsql.h"

#define DB_TABLE_CADELE "cab_ele"

struct DbCabEleItem : public DbBasicItem{
    double vol, cur, pow, ele;
};


class DbCabEle : public SqlBasic<DbCabEleItem>
{
    DbCabEle();
public:
    static DbCabEle *bulid();
    virtual QString tableName(){return QString("%1").arg(DB_TABLE_CADELE) ;}
    bool insertItem(DbCabEleItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const DbCabEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbCabEleItem &item);
};


#endif // DBMAINELE_H
