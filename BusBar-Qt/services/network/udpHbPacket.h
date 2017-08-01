/*
 * udpHbPacket.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef UDP_UDPHBPACKET_H_
#define UDP_UDPHBPACKET_H_

#include "udpservice.h"

#define UDP_SERVER_OK	20 /*服务端正常*/
#define UDP_SERVER_ERR	0 /*服务端错误*/

char* udp_getServerIP(void);
void udp_hb_thread(void);
void udp_hb_stop(void);
extern char gUdpCount; // 大于0服务端在线   否则服务端离线

#endif /* UDP_UDPHBPACKET_H_ */
