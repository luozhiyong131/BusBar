#ifndef BUS_LINETABLEWID_H
#define BUS_LINETABLEWID_H

#include "bus_box/bus_boxlinetablewid.h"

class BUS_LineTableWid : public BUS_BoxLineTableWid
{
    Q_OBJECT
public:
    explicit BUS_LineTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setObjUnit(sObjData *unit, QStringList &list);
};

#endif // BUS_LINETABLEWID_H
