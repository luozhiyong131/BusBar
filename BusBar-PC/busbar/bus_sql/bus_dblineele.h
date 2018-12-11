#ifndef BUS_DBMAINELE_H
#define BUS_DBMAINELE_H

#include "bus_dbname.h"

#define DB_TABLE_MAINELE "bus_lineele"

struct DbLineEleItem : public DbBasicItem{
    double line_1, line_2, line_3, line;
};


class BUS_DbLineEle : public SqlBasic<DbLineEleItem>
{
public:
    BUS_DbLineEle();

    virtual QString tableName(){return QString("%1_%2").arg(DB_TABLE_MAINELE).arg(mId) ;}
    bool insertItem(DbLineEleItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const DbLineEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbLineEleItem &item);
    int mId;
};

class DbLineEle1 : public BUS_DbLineEle
{
public:
    DbLineEle1(){ mId=1; createTable(); }
};

class DbLineEle2 : public BUS_DbLineEle
{
public:
    DbLineEle2(){ mId=2; createTable(); }
};

class DbLineEle3 : public BUS_DbLineEle
{
public:
    DbLineEle3(){ mId=3; createTable(); }
};

class DbLineEle4 : public BUS_DbLineEle
{
public:
    DbLineEle4(){  mId=4; createTable(); }
};

BUS_DbLineEle* bus_lineEle_db(int id);
#endif // DBMAINELE_H
