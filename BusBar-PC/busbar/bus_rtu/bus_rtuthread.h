#ifndef BUS_RTUTHREAD_H
#define BUS_RTUTHREAD_H

#include "bus_rtutrans.h"

class BUS_RtuThread : public RtuThread
{
    Q_OBJECT
public:
    explicit BUS_RtuThread(QObject *parent = nullptr);

signals:

protected slots:
    void initSlot();

private:
    BUS_RtuTrans *mRtu;
};

#endif // BUS_RTUTHREAD_H
