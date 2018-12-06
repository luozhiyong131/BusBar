#ifndef DBLINETHRESHOLDS_H
#define DBLINETHRESHOLDS_H
#include "dblinerecords.h"


struct DbLineThresholdItem : public DbBasicItem {
    int dev_id, line;
    double vol, vol_min, vol_max, cur, cur_min, cur_max;
};

class DbLineThresholds : public SqlBasic<DbLineThresholdItem>
{
public:
    DbLineThresholds();

    bool insertItem(DbLineThresholdItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbLineThresholdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbLineThresholdItem &item);
};

#endif // DBLINETHRESHOLDS_H
