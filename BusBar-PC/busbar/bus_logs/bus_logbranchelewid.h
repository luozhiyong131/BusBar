#ifndef BUS_LOGBRANCHELEWID_H
#define BUS_LOGBRANCHELEWID_H

#include "bus_loglineelewid.h"

class BUS_LogBranchEleWid : public BUS_LogLineEleWid
{
    Q_OBJECT
public:
    explicit BUS_LogBranchEleWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUS_LOGBRANCHELEWID_H
