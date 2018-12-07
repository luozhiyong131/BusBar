#ifndef BUS_BOXLINETABLEWID_H
#define BUS_BOXLINETABLEWID_H

#include "bus_boxlooptablewid.h"

class BUS_BoxLineTableWid : public BUS_BoxLoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_BoxLineTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setTemAlarm(sDataUnit *unit, int row);
    void setAlarm(sObjData *unit, int row);
    void setObjUnit(sObjData *unit, QStringList &list);
    int updateDev(sDataPacket *dev, int row);
};

#endif // BUS_BOXLINETABLEWID_H
