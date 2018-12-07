#ifndef BUS_RTUTHREAD_H
#define BUS_RTUTHREAD_H
#include "common.h"
#include "bus_rtutrans.h"

class BUS_RtuThread : public RtuThread
{
    Q_OBJECT
public:
    explicit BUS_RtuThread(QObject *parent = nullptr);
    void init(int id) {mBusId=id;}

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    int mBusId;
    BUS_RtuTrans *mRtu;
};

#endif // BUS_RTUTHREAD_H
