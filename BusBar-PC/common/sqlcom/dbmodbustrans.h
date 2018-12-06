#ifndef DBMODBUSTRANS_H
#define DBMODBUSTRANS_H
#include "dbmodbuscmd.h"

struct DbModbusTransItem : public DbBasicItem {
    int dev_id;
    QString state;
    int all_count, ok_count, err_count;
};

class DbModbusTrans : public SqlBasic<DbModbusTransItem>
{
public:
    DbModbusTrans();
    bool insertItem(DbModbusTransItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbModbusTransItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbModbusTransItem &item);
};

#endif // DBMODBUSTRANS_H
