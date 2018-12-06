#ifndef DBLINERECORDS_H
#define DBLINERECORDS_H
#include "dbmodbustrans.h"

struct DbLineRecordItem : public DbBasicItem {
    int dev_id, line, sw;
    QString sw_str;
    double vol, cur, pow, apow, pf, ele;
};


class DbLineRecords : public SqlBasic<DbLineRecordItem>
{
public:
    DbLineRecords();

    bool insertItem(DbLineRecordItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbLineRecordItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbLineRecordItem &item);
};

#endif // DBLINERECORDS_H
