#ifndef RTUTRANS_H
#define RTUTRANS_H
#include "rtusentcom.h"
#include "rtuzmrecv.h"

class RtuTrans : public QThread
{
public:
    RtuTrans(QObject *parent = nullptr);

     bool setValue(const sRtuSetCmd &cmd);
     virtual bool sentSetCmd(int addr, int reg, ushort value, int msecs) = 0;

protected:
    void getAlarm(sDataUnit &data);
    void dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data, int rate=1);
    void devObjData(ZM_sObjData &rtuData, int i, sObjData &data , bool flag);
    void devData(ZM_sRtuPacket &rtuData, sDevData &data);
    void envData(ZM_sEnv &rtuData, sEnvData &data);
    void devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet);

    QMap<int , ushort> mRecordPf;
};

#endif // RTUTRANS_H
