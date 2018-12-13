#include "setrtucmd.h"
#include "bus_rtu/bus_rtuthread.h"

extern BUS_RtuTrans *g_RtuTrans[4];

SetRtuCmd::SetRtuCmd(QObject *parent) : QThread(parent)
{

}

void SetRtuCmd::sendData(int busID, int addr, ushort reg, ushort len)
{
    BUS_RtuTrans *rtu = g_RtuTrans[busID];

    if((busID == 0xff) || (addr == 0xff)){
        for(int i=0; i<4; ++i) {
            if(g_RtuTrans[i]) g_RtuTrans[i]->sentSetCmd(addr, reg, len);
        }
    } else {
        if(rtu) rtu->sentSetCmd(addr, reg, len);
    }
}

void SetRtuCmd::sendReg(int reg, sThresholdItem &item)
{
    sendData(item.bus, item.box, reg, item.max);
    sendData(item.bus, item.box, reg+1, item.min);
}

void SetRtuCmd::send(sThresholdItem &item)
{
    int reg=0;
    switch (item.type) {
    case 1: reg = VoltageMAX_L1 + item.num*2; break;
    case 2: reg = CurrentMAX_L1 + item.num*2; break;
    case 3: reg = temperatureMAX_1 + item.num*2; break;
    }
    sendReg(reg, item);
}
