#ifndef UDPRECVSOCKET_H
#define UDPRECVSOCKET_H

#include "udp/sent/udpsentsocket.h"

#define UDP_PORT_NUM 20

class UdpRecvSocket
{
public:
    explicit UdpRecvSocket();
    ~UdpRecvSocket();

    int recvData(int id, int portNum, uchar *buf);
    int recvData(int id, int portNum, QString &ip, uchar *buf);
};

#endif // UDPRECVSOCKET_H
