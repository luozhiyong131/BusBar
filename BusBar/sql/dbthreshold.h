#ifndef DBTHRESHOLD_H
#define DBTHRESHOLD_H

#include "basicsql.h"

#define DB_TABLE_THRESHOLD "threshold"

struct DbThresholdItem{
    int id;
    int bus; // 母线编号 1~4
    int type; // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值
    int num; // 编号
    int min, crmin, crmax, max; // 最小值，临界下限  临界上限  最大值
};

class DbThreshold : public SqlBasic<DbThresholdItem>
{
    DbThreshold();
public:
    static DbThreshold* bulid();

    bool saveItem(DbThresholdItem &item); // 单一设置

    void unifiedSet(DbThresholdItem &item); // 统一设置
    void globalSet(DbThresholdItem &item); // 全局设置
    void globalUnifiedSet(DbThresholdItem &item); // 全局统一设置

protected:
    bool insertItem(DbThresholdItem &item); // 插入
    bool updateItem(const DbThresholdItem &item);

    bool modifyItem(const DbThresholdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbThresholdItem &item);

    int getId(DbThresholdItem &item);
    QString tableName(){return QString("%1").arg(DB_TABLE_THRESHOLD);}

    void  updateThreshold(DbThresholdItem &item, const QString &cmd);
};

#endif // DBTHRESHOLD_H
