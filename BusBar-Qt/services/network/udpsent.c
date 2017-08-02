/*
 * udpsent.c
 * UDP客户端 	实现UDP数据的发送功能
 *	1、自动创建套接字
 *	2、端口号会随机分配
 *	3、数据发送前，检查服务端是滞在线, 否则不发送
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "udpsent.h"

#include <time.h>
#include <netdb.h>

#define udp_PORT_SIZE 20 // udp 端口号的个数

static int sock_fd=-1; /*套按字*/
static int port = 28720;
static struct sockaddr_in server_addr;
static char *server_ip = NULL;

/* 创建一个socket，类型是SOCK_DGRAM，udp类型*/
static int udp_creatSocket(void)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		udp_printf("udp Client Creat Socket Err\n");

	return sock;
}

/* 初始化预连接的服务端地址*/
static void udp_initServerAddr(void)
{
	char* url = server_ip;
//	printf("%s\n",url);

	struct hostent *host= (struct hostent *) gethostbyname(url); /* 通过函数入口参数url获得host地址（如果是域名，会做域名解析）*/

	/* 初始化预连接的服务端地址 */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
}


/**
 * 初始化套接字，初始化端口号
 */
static void udp_initSocket(void)
{
	if(sock_fd < 0)
	{
		sock_fd = udp_creatSocket(); // 创建套接字
		if(sock_fd< 0)
			udp_printf("udp init Socket Err\n");

		srand(time(0)); // 获取真的随机数
        port = 28720 + rand()%udp_PORT_SIZE; // 随机分配一个端口
		server_ip = udp_getServerIP();
	}
}



/**
 * 功  能：udp 发送数据条件检查
 * 返  回：true
 */
static int udp_sentCheck(void)
{
	int ret = false;
	udp_initSocket();

	/*发送的条件，有套接字， 有服务端IP，倒计时大于0*/
	if((sock_fd>=0)&&(strlen(server_ip) > 0) && (gUdpCount > 2))
		ret = true;
//	else
//		udp_debug("udp sent check Err!\n");

	return ret;
}



/**
 * 功能：udp 数据发送
 * 入口参数：*send_data -> 数据缓冲区  len -> 数据长度
 * 出口参数：
 * 返回: 发送长度，
 */
int udp_clientSentData(uchar *send_data, uint len)
{
	int ret=0, sockfd=sock_fd;

	ret = udp_sentCheck();	/*服务端检查*/
	if(ret == true)
	{
		udp_initServerAddr();

		/* 发送数据到服务远端 */
		ret = sendto(sockfd, send_data, len, 0,
				(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		udp_udelay(5*1000);  // 短延时
	}

	return ret;
}

/**
 * 关闭客户端 套接字
 */
void udp_clientClose(void)
{
	close(sock_fd);
}
