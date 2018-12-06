#ifndef DBMODBUSCMD_H
#define DBMODBUSCMD_H
#include "dbenv.h"

struct DbModbusCmdItem : public DbBasicItem {
    int dev_id;
    QString msg;
};

class DbModbusCmd : public SqlBasic<DbModbusCmdItem>
{
public:
    DbModbusCmd();

    bool insertItem(DbModbusCmdItem &item); // 插入
    void createTable();
protected:
    bool modifyItem(const DbModbusCmdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,DbModbusCmdItem &item);
};

#endif // DBMODBUSCMD_H
