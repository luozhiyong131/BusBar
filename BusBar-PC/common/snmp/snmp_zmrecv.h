#ifndef SNMP_ZMRECV_H
#define SNMP_ZMRECV_H
#include "snmpthread.h"

class SNMP_ZmRecv
{
public:
    SNMP_ZmRecv();

    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);

protected:
    int getItemByOid(int id);
    void getMS(const QByteArray &oid);
    void devInfo(const QByteArray &data);
    virtual void devTypeData(int value, sDataPacket *pkt)=0;

    void lineData(const QByteArray &data);
    void loopData(const QByteArray &data);
    void envData(const QByteArray &data);
    void outputCur(const QByteArray &data);
    void outputData(const QByteArray &data);

protected:
    int mRate;
    QString mIP, mOid;
    sDevPackets *mPackets;
    sDataPacket *mDataPacket;
};

#endif // SNMP_ZMRECV_H
