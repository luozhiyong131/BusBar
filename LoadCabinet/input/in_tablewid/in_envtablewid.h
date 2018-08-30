#ifndef IN_ENVTABLEWID_H
#define IN_ENVTABLEWID_H

#include "in_transtablewid.h"

class IN_EnvTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit IN_EnvTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(sEnvData &unit, int id, int row);
    void setObjUnit(sEnvData &unit, int id, QStringList &list);
    int updateDev(sDataPacket *dev, int row);
};

#endif // IN_ENVTABLEWID_H
