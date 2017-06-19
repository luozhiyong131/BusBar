#ifndef DBMAINELE_H
#define DBMAINELE_H

#include "basicsql.h"

#define DB_TABLE_MAINELE "main_ele"

struct DbMainEleItem : public DbBasicItem{
    int line_1, line_2, line_3, line;
};


class DbMainEle : public SqlBasic<DbMainEleItem>
{
public:
    DbMainEle();

    static DbMainEle* bulid();
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_MAINELE).arg(1) ;}
    bool insertItem(DbMainEleItem &item); // 插入

protected:
    bool modifyItem(const DbMainEleItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbMainEleItem &item);
};


class DbMainEle2 : public DbMainEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_MAINELE).arg(2) ;}
};

class DbMainEle3 : public DbMainEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_MAINELE).arg(3) ;}
};

class DbMainEle4 : public DbMainEle
{
public:
    QString tableName(){return QString("%1_%2").arg(DB_TABLE_MAINELE).arg(4) ;}
};
#endif // DBMAINELE_H
