#ifndef BUS_BRANCHTABLEWID_H
#define BUS_BRANCHTABLEWID_H

#include "bus_box/bus_boxdlg.h"

class BUS_BranchTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit BUS_BranchTableWid(QWidget *parent = nullptr);

    void initFun(int bus);

protected slots:
    void busChangeSlot(int);
    void timeoutDone();

protected:
    virtual void initWid();
    virtual QString setAlarm(sDataPacket *dev, int row);
    virtual void setObjUnit(sObjData *unit, QStringList &list);
    virtual int updateDev(sDataPacket *dev, int row);
    virtual void updateData();

protected:
    sDevPackets *mPackets;
};

#endif // BUS_BRANCHTABLEWID_H
