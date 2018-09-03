#ifndef IN_RTUTRANS_H
#define IN_RTUTRANS_H
#include "in_rturecv.h"
#include "in_com/in_datapackets.h"
#include "serialtrans.h"

class IN_RtuTrans
{
    IN_RtuTrans();
public:
    static IN_RtuTrans *bulid();

    void init(SerialTrans *serial);
    int transmit(int addr, sDataPacket *packet, int msecs); //发送数据并回收
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    bool sentSetCmd(sRtuSentCom &cmd, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void getAlarm(sDataUnit &data);
    void objData(IN_sRtuLine *data, sObjData *obj);
    void devData(IN_sRtuRecv *pkt, sDevData *dev);
    void envData(IN_sRtuRecv *pkt, sDevData *dev);
    int transData(int addr, IN_sRtuRecv *pkt, int msecs);
    void sleep(unsigned int msec);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    QMutex *mMutex;
    bool isRun;

    IN_sRtuRecv *mRtuPkt;
    IN_RtuRecv *mRtuRecv;
    IN_RtuSent *mRtuSent;
    SerialTrans *mSerial;
};

#endif // IN_RTUTRANS_H
