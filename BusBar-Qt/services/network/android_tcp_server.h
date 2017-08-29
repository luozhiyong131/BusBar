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

#define ANDROID_TCP_PORT	11283  // 案桌TCP端口号

void android_tcpServer_thread(void);
void android_tcpServer_stop(void);
int android_sent(uchar *buf, int len);

#endif /* ANDROID_ANDROID_TCP_SERVER_H_ */
