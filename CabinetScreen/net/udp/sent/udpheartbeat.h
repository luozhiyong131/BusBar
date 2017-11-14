#ifndef UDPHEARTBEAT_H
#define UDPHEARTBEAT_H

#include "udpsentsocket.h"

class UdpHeartBeat
{
public:
    void heartbeatPacket(int id, const QString &ip);
};

#endif // UDPHEARTBEAT_H
