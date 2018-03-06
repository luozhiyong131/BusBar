#ifndef DBTHRESHOLD_H
#define DBTHRESHOLD_H

#include "basicsql.h"

#define DB_TABLE_THRESHOLD "threshold"

struct DbThresholdItem{
    int id;
    int bus; // 母线编号 0~3
    int type; // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5接插箱温度  6 回路电压阈值
    int num; // 编号
    int min, crmin, crmax, max; // 最小值，临界下限  临界上限  最大值
};

class DbThreshold : public SqlBasic<DbThresholdItem>
{
    DbThreshold();
public:
    static DbThreshold* bulid();

    bool saveItem(DbThresholdItem &item); // 单一设置
    bool getItem(DbThresholdItem &item);

    void setLoopCurAll(DbThresholdItem &item); // 设置所有回路电流
    void setTempAll(DbThresholdItem &item); // 设置所有回路温度

    void setLineVolAll(DbThresholdItem &item); // 设置成有主路电压
    void setLineCurAll(DbThresholdItem &item); // 设置成有主路电流
    void setLineTempAll(DbThresholdItem &item); // 设置所有温度
    void setAll(DbThresholdItem &item);

protected:
     void createTable();
    bool insertItem(DbThresholdItem &item); // 插入
    bool updateItem(const DbThresholdItem &item);

    bool modifyItem(const DbThresholdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbThresholdItem &item);

    int getId(DbThresholdItem &item);
    QString tableName(){return QString("%1").arg(DB_TABLE_THRESHOLD);}

    void  updateThreshold(DbThresholdItem &item, const QString &cmd);
};

#endif // DBTHRESHOLD_H
