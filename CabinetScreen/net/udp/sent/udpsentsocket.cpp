/*
 * udpsentsocket.cpp
 * UDP 发送套接字
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "udpsentsocket.h"

/***********************************C语言实现********************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <ctype.h>


static int sock_fd[]={-1, -1}; /*套按字*/
static char *ifName[] ={ETH_ONE, ETH_TWO};

static struct sockaddr_in server_addr[IF_ETH_NUM];

/* 创建一个socket，类型是SOCK_DGRAM，udp类型*/
static int udp_creatSocket(int i)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        qDebug("udp Client Creat Socket Err\n");        
    } else {


    }

    return sock;
}

/* 初始化预连接的服务端地址*/
static void udp_initServerAddr(int i, char *server_ip, int port)
{
    char* url = server_ip;
//	printf("%s\n",url);

    struct hostent *host= (struct hostent *) gethostbyname(url); /* 通过函数入口参数url获得host地址（如果是域名，会做域名解析）*/

    /* 初始化预连接的服务端地址 */
    server_addr[i].sin_family = AF_INET;
    server_addr[i].sin_port = htons(port);
    server_addr[i].sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(server_addr[i].sin_zero), 0, sizeof(server_addr[i].sin_zero));
}

static void udp_initSocket(int i)
{
    if(sock_fd[i] < 0)
    {
        sock_fd[i] = udp_creatSocket(i); // 创建套接字
    }
}

/**
 * 功能：udp 数据发送
 * 入口参数：*send_data -> 数据缓冲区  len -> 数据长度
 * 出口参数：
 * 返回: 发送长度，
 */
static int udp_clientSentData(int i, char *ip, int port, uchar *send_data, uint len)
{
    int ret=0, sockfd=sock_fd[i];

    udp_initSocket(i);	/*服务端检查*/
    udp_initServerAddr(i, ip, port);

//    struct ifreq interface;
//    strncpy(interface.ifr_ifrn.ifrn_name, ifName[i], strlen(ifName[i]));
//    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
//                   (char *)&interface, sizeof(interface))  < 0) {
//           qDebug() << " udp_creatSocket SO_BINDTODEVICE failed " << ifName[i];
//    } else {
//        qDebug() << "OK";
//    }

    struct ifreq interface;
       strncpy(interface.ifr_ifrn.ifrn_name, ifName[i], strlen(ifName[i]) +1 );
       if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(interface))  < 0) {
              perror("SO_BINDTODEVICE failed");
       } else {
           qDebug() << "AAAAAAAAA";
       }


    /* 发送数据到服务远端 */
    ret = sendto(sockfd, send_data, len, 0,
                 (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    return ret;
}

void udp_sent_data(int i, const QString &ip, int port, uchar *buf, uint len)
{
    udp_clientSentData(i, ip.toLatin1().data(),port, buf, len);
}

void udp_sent_data(int i, const QString &ip, uchar *buf, uint len)
{
   udp_sent_data(i, ip, UDP_SENT_PORT, buf, len);
}
