/*
 * android_tcp_server.h
 *
 *  Created on: 2016年9月19日
 *      Author: lzy
 */

#ifndef ANDROID_ANDROID_TCP_SERVER_H_
#define ANDROID_ANDROID_TCP_SERVER_H_

#include "tcpserver.h"
#include "netDataSegment.h"

void android_tcpServer_thread(void);
void android_tcpServer_stop(void);
int android_sent(uchar *buf, int len);

#endif /* ANDROID_ANDROID_TCP_SERVER_H_ */
