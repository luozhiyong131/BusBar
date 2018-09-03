#ifndef IN_RTURECV_H
#define IN_RTURECV_H
#include "in_rtupacket.h"

class IN_RtuRecv
{
public:
    IN_RtuRecv();

    bool recvPacket(uchar *buf, int len, IN_sRtuRecv *pkt);

protected:
    bool rtuRecvCrc(uchar *buf, int len, IN_sRtuRecv *msg);
    int rtuRecvLen(uchar *buf, int len);
    int rtuRecvHead(uchar *ptr,  IN_sRtuRecv *pkt);
    int rtuRecvData(uchar *ptr, IN_sRtuLine *msg);
    int rtuRecvEnv(uchar *ptr, IN_sRtuEnvUnit *msg);
    void rtuRecvSwap(IN_sRtuRecv *pkt);
};

#endif // IN_RTURECV_H
