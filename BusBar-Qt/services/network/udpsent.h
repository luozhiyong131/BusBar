/*
 * udpsent.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef UDP_UDPSENT_H_
#define UDP_UDPSENT_H_
#include "udpHbPacket.h"

int udp_clientSentData(uchar *send_data, uint len);
void udp_clientClose(void);

#endif /* UDP_UDPSENT_H_ */
