#ifndef DBENV_H
#define DBENV_H
#include "dbalarm.h"

struct DbEnvItem : public DbBasicItem {
    DbEnvItem() {sensor_id=1;}
    int dev_id, sensor_id;
    int tem, tem_min, tem_max, hum, hum_min, hum_max;
};


class DbEnv : public SqlBasic<DbEnvItem>
{
public:
    DbEnv();

    bool insertItem(DbEnvItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbEnvItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbEnvItem &item);

};

#endif // DBENV_H
