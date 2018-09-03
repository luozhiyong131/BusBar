#ifndef LINETABLEWID_H
#define LINETABLEWID_H

#include "comtablewid.h"

class LineTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit LineTableWid(QWidget *parent = nullptr);

protected slots:
    void timeoutDone();

protected:
    virtual void initWid();
    virtual void setAlarm(sObjData &unit, int row);
    virtual void setObjUnit(sObjData &unit, QStringList &list);
    virtual int updateDev(sDataPacket *dev, int row);
    virtual void updateData();
};

#endif // LINETABLEWID_H
