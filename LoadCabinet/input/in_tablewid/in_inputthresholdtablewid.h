#ifndef IN_INPUTTHRESHOLDTABLEWID_H
#define IN_INPUTTHRESHOLDTABLEWID_H

#include "in_inputtablewid.h"

class IN_InputThresholdTableWid : public IN_InputTableWid
{
    Q_OBJECT
public:
    explicit IN_InputThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(sObjData &unit,int row);
    void setObjUnit(sObjData &unit, QStringList &list);
};

#endif // IN_INPUTTHRESHOLDTABLEWID_H
