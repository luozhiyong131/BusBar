#ifndef IN_TRANSTABLEWID_H
#define IN_TRANSTABLEWID_H

#include "tablewid/linetablewid.h"

class IN_TransTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit IN_TransTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(int err, int row);
    void setObjUnit(sRtuCount &unit, QStringList &list);
    int updateDev(sDataPacket *dev, int row);
};

#endif // IN_TRANSTABLEWID_H
