#ifndef BUS_DBBRANCHELE_H
#define BUS_DBBRANCHELE_H

#include "bus_dbalarm.h"

#define DB_TABLE_BRANCHELE "bus_branchele"

struct DbBranchEleItem : public DbBasicItem{
    QString name;
    double loops[10], loop;
};


class BUS_DbBranchEle : public SqlBasic<DbBranchEleItem>
{
public:
    BUS_DbBranchEle();

    QString tableName(){return QString("%1_%2").arg(DB_TABLE_BRANCHELE).arg(mId) ;}
    bool insertItem(DbBranchEleItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const DbBranchEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbBranchEleItem &item);
    int mId;
};

class DbBranchEle1 : public BUS_DbBranchEle
{
public:
    DbBranchEle1(){ mId=1; createTable(); }
};

class DbBranchEle2 : public BUS_DbBranchEle
{
public:
    DbBranchEle2(){ mId=2; createTable(); }
};


class DbBranchEle3 : public BUS_DbBranchEle
{
public:
    DbBranchEle3(){ mId=3; createTable(); }
};

class DbBranchEle4 : public BUS_DbBranchEle
{
public:
    DbBranchEle4(){ mId=4; createTable(); }
};

BUS_DbBranchEle* bus_branchEle_db(int id);
#endif // DBBRANCHELE_H
