#ifndef UDPRECVSOCKET_H
#define UDPRECVSOCKET_H

#include "udp/sent/udpsentsocket.h"


class UdpRecvSocket
{
public:
    explicit UdpRecvSocket();

    int recvData(int id, uchar *buf);
    int recvData(int id, QString &ip, uchar *buf);
};

#endif // UDPRECVSOCKET_H
