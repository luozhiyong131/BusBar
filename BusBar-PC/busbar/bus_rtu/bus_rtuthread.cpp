#include "bus_rtuthread.h"

BUS_RtuThread::BUS_RtuThread(QObject *parent) : RtuThread(parent)
{

}


void BUS_RtuThread::initSlot()
{
    SerialPort *serial = M_ConfigFile::bulid()->item->serial;
    mPackets = BUS_DataPackets::bulid()->packets;
    mRtu = M_RtuTrans::bulid();

    if(serial) {
        mRtu->init(serial);
    } else {
         QTimer::singleShot(1400,this,SLOT(initSlot()));
    }
}
