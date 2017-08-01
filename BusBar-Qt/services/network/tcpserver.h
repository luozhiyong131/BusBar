/*
 * tcpserver.h
 *
 *  Created on: 2016年8月5日
 *      Author: lzy
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_
#include "udpdebug.h"



int tcp_creatSocket(int port, int lisnum);
void tcp_server_thread(void);
void tcp_server_stop(void);

#endif /* TCPSERVER_H_ */
