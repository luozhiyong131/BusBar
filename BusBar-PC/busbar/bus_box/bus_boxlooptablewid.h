#ifndef BUS_BOXLOOPTABLEWID_H
#define BUS_BOXLOOPTABLEWID_H

#include "comtablewid.h"
#include "bus_com/bus_datapackets.h"

class BUS_BoxLoopTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit BUS_BoxLoopTableWid(QWidget *parent = nullptr);

     void initFun(int bus, int box);

protected slots:
   virtual void timeoutDone();

protected:
    virtual void initWid();
    virtual void setAlarm(sObjData *unit, int row);
    virtual void setObjUnit(sObjData *unit, QStringList &list);
    virtual int updateDev(sDataPacket *dev, int row);
    virtual void updateData();

protected:
    sDataPacket *mPacket;
};

#endif // BUS_BOXLOOPTABLEWID_H
