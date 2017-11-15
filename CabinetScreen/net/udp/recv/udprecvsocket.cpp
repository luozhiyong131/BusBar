/*
 * UdpRecvSocket.cpp
 * UDP 接收套接字
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "udprecvsocket.h"
#define UDP_RECV_PORT  28720  /* 接收套接字起始端口 */
#define UDP_BUF_SIZE 255

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>


static int sock_fd[IF_ETH_NUM][UDP_PORT_NUM]={-1, -1};
static char *ifName[] ={ETH_ONE, ETH_TWO};


static void set_socket(int sockfd, int i)
{
    struct ifreq interface;
    strncpy(interface.ifr_ifrn.ifrn_name, ifName[i], strlen(ifName[i])+1);
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,(char *)&interface, sizeof(interface));
    if (ret < 0) {
        qDebug() << "udp_serviceSocket SO_BINDTODEVICE failed " << ifName[i];
    }

    /*超时设置*/
    struct timeval timeout={0,10};//3S
    ret=setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
    if(ret<0)
        qDebug("UDP setsockopt Err\n");

}



/**
 * 功能：创建UDP服务端套接字
 * 返回 ：套接字
 */
static int udp_serviceSocket(int port)
{
    int sockfd;
    struct sockaddr_in server_addr;/* 主机IP地址和端口号 */

    /* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        qDebug("Socket error\n");
        return -1;
    }

    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;		/*IPv4因特网域*/
    server_addr.sin_port = htons(port);    /*端口号，这里进行网络字节序的转换 */
    //	server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));


    /* 绑定socket到服务端地址 */
    if (bind(sockfd, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        /* 绑定地址失败 */
        qDebug("Bind error\n");
        return -1;
    }
    //    qDebug("UDP Server Waiting for client on port %d...\n", port);

    return sockfd;
}



/**
 * 功  能：UDP 数据接收
 * 出口参数：*recv_data -> 接收数据缓冲区
 * 返  回: 数据长度
 */
static int udp_serviceRecvData(int sockfd,struct sockaddr_in *client_addr,uchar *recv_data)
{
    int ret=0;
    uint addr_len = sizeof(struct sockaddr);


    /* 从sock中收取最大BUF_SIZE - 1字节数据 */
    /* UDP不同于TCP，它基本不会出现收取的数据失败的情况，除非设置了超时等待 */
    ret = recvfrom(sockfd, recv_data, UDP_BUF_SIZE - 1, 0,
                   (struct sockaddr *)client_addr, &addr_len);
    //	udp_printf("UDP Recv Data len:%d %s\n",ret, recv_data);
    return ret;
}


/**
 * @brief 构造函数
 * @param parent
 */
UdpRecvSocket::UdpRecvSocket()
{
    for(int i=0; i<IF_ETH_NUM; ++i)
    {
        for(int k=0; k<UDP_PORT_NUM; ++k) {
            sock_fd[i][k] = udp_serviceSocket(UDP_RECV_PORT + k);
            set_socket(sock_fd[i][k], i);
        }
    }
}

UdpRecvSocket::~UdpRecvSocket()
{
    for(int i=0; i<IF_ETH_NUM; ++i)
    {
        for(int k=0; k<UDP_PORT_NUM; ++k) {
            close(sock_fd[i][k]);
        }
    }
}


int UdpRecvSocket::recvData(int id, int portNum, QString &ip, uchar *buf)
{
    static struct sockaddr_in pin;

    int rtn = udp_serviceRecvData(sock_fd[id][portNum], &pin, buf);
    if(rtn > 0) {
        ip = inet_ntoa(pin.sin_addr);
    }

    return rtn;
}


int UdpRecvSocket::recvData(int id, int portNum, uchar *buf)
{
    static QString ip;

    return recvData(id, portNum, ip, buf);
}
