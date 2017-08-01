/*
 * udpdebug.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef UDP_UDPDEBUG_H_
#define UDP_UDPDEBUG_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>


#define TRUE  	1
#define FALSE  0
#define true TRUE
#define false FALSE

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define udp_printf printf
#define udp_udelay  usleep
#define udp_delay   sleep

#endif /* UDP_UDPDEBUG_H_ */
