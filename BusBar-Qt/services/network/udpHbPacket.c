/*
 * udpHbPacket.c
 * UDP心跳包
 * 	1、启动线程接收心跳包
 * 	2、获取到正确的心跳包时，自动获取服务端地址、及设置标志位
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "udpHbPacket.h"

#define UDP_HBPORT_NUM    18725 // 心跳端口
#define UDP_HEARTBEAT_MSG   "Clever-Manager PDU APP Server OK!"

static int sock_fd=-1; /*套按字*/
char gUdpCount = 0; //UDP_SERVER_OK; /* 20 表示与服务端连接状态  0为断开*/
static char server_ip[20] = {"192.168.1.102"}; /*服务器IP地址*/
static pthread_t threadId;

/**
 * 功能：初始化UDP
 * 返回 ：套接字
 */
static int udp_initSocket(void)
{
	int ret = true;
	if(sock_fd<0)
	{
		ret = udp_serviceSocket(UDP_HBPORT_NUM); // 创建套接 字
		if(ret< 0)
			udp_printf("UDP Connect Err\n");
		else
			sock_fd = ret;
	}

	return ret;
}



/**
 * 功  能：服务端心跳包判断
 * 入口参数：*send_data -> 数据缓冲区
 * 返回: true  表示是心跳包
 */
static int udp_heartbeatPacket(uchar *recv_data)
{
	int ret = strncmp((char *)recv_data,UDP_HEARTBEAT_MSG,strlen(UDP_HEARTBEAT_MSG));
	if(ret == 0)
	{
		gUdpCount = UDP_SERVER_OK;
		ret = true;
	}
	else
		ret = false;

	return ret;
}


/**
 * 功能：保存服务端 IP地址相关信息
 */
static int udp_serverIP(struct sockaddr_in *client_addr)
{
	memset(server_ip, 0, sizeof(server_ip));
	sprintf(server_ip,"%s", inet_ntoa(client_addr->sin_addr)); /*获取服务端IP*/
	//rt_kprintf("Server:(%s , %d)\n", server_ip,ntohs(client_addr->sin_port));

	return 0;
}


/**
 * 功  能：UDP 数据接收
 * 出口参数：*recv_data -> 接收数据缓冲区
 * 返  回: 数据长度
 */
static void udp_hbRecvData(void)
{
	static uchar recv_data[UDP_BUF_SIZE]={0};
	int sockfd=sock_fd;
	static struct sockaddr_in client_addr;/* 客户端IP地址和端口号 */

	int ret = udp_serviceRecvData(sockfd, &client_addr, recv_data);
	if(ret > 0)
	{
		ret = udp_heartbeatPacket(recv_data); /*心跳包检查*/
		if(ret == true)
		{
			udp_serverIP(&client_addr);
//			udp_printf("UDP heart beat Packet OK\n");
		}
	}
}

/**
 * 功  能：获取服务端IP
 * 返  回:
 */
char* udp_getServerIP(void)
{
	return server_ip;
}

/**
 * 线程入口函数
 */
static void udp_thread_entry(void)
{
	int ret  = udp_initSocket();
	if(ret < 0)
	{
		udp_printf("UDP init heart beat Packet Socket Err!\n");
		return ;
	}

	while(1)
	{
		udp_delay(1);
		udp_hbRecvData();
	}
}


/**
 * 线程计时入口函数
 */
static void udp_thread_count(void)
{
	while(1)
	{
		udp_delay(1);
        if(gUdpCount>0)  ///====
            gUdpCount--; /*发送一次减少一次 */
	}
}

/**
 * 创建并启动计时线程
 */
void udp_count_thread(void)
{
    #if 0
	pthread_t id;
	int ret = pthread_create(&id, NULL, (void *)udp_thread_count, NULL);
	if(ret != 0)
		udp_printf("create count pthread err\n");
#else
    udp_thread_count();
#endif
}


/**
 * 创建并启动心跳包线程
 */
void udp_hb_thread(void)
{
#if 0
	pthread_t *id = &threadId;
	int ret = pthread_create(id, NULL, (void *)udp_thread_entry, NULL);
	if(ret != 0)
		udp_printf("create hb pthread err\n");

	udp_count_thread();
#else
    udp_thread_count();
#endif
}

/**
 * 终止线程
 */
void udp_hb_stop(void)
{
	close(sock_fd);

#if 0
	pthread_cancel(threadId);
#endif
}



