#ifndef IN_INPUTTABLEWID_H
#define IN_INPUTTABLEWID_H

#include "in_envtablewid.h"

class IN_InputTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit IN_InputTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    int updateDev(sDataPacket *dev, int row);
};

#endif // IN_INPUTTABLEWID_H
