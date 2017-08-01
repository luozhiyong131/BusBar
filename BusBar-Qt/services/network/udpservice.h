/*
 * udpservice.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef UDP_UDPSERVICE_H_
#define UDP_UDPSERVICE_H_
#include "udpdebug.h"

#define UDP_BUF_SIZE	256 /*数据缓冲区大小， IP设备使用256， ARM9系列设备使用512*/

int udp_serviceSocket(int port);
int udp_serviceRecvData(int sockfd,struct sockaddr_in *client_addr,uchar *recv_data);

#endif /* UDP_UDPSERVICE_H_ */
