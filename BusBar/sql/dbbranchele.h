#ifndef DBBRANCHELE_H
#define DBBRANCHELE_H

#include "basicsql.h"

#define DB_TABLE_BRANCHELE "branch_ele"

struct DbBranchEleItem : public DbBasicItem{
    QString name;
    double loop_1, loop_2, loop_3, loop;
};


class DbBranchEle : public SqlBasic<DbBranchEleItem>
{
public:
    DbBranchEle();

    static DbBranchEle* bulid();
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_BRANCHELE).arg(1) ;}
    bool insertItem(DbBranchEleItem &item); // 插入

protected:
    bool modifyItem(const DbBranchEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbBranchEleItem &item);
};



class DbBranchEle2 : public DbBranchEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_BRANCHELE).arg(2) ;}
};


class DbBranchEle3 : public DbBranchEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_BRANCHELE).arg(3) ;}
};

class DbBranchEle4 : public DbBranchEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_BRANCHELE).arg(4) ;}
};
#endif // DBBRANCHELE_H
