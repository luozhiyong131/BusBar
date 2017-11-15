/*
 * udpheartbeat.cpp
 * UDP 心跳包线程
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "udpheartbeat.h"

#define UDP_HEARTBEAT_MSG   "Clever-Manager PDU PC Server OK!" // 心跳包


void UdpHeartBeat::heartbeatPacket(int id, const QString &ip)
{
    udp_sent_data(id, ip, UDP_HB_PORT,
                  (uchar *)UDP_HEARTBEAT_MSG,
                  strlen(UDP_HEARTBEAT_MSG));
}


