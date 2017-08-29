/*
 * android_tcp_server.c
 *
 *  Created on: 2016年9月19日
 *      Author: lzy
 */
#include "android_tcp_server.h"

//#define ANDROID_TCP_PORT	11283  // 案桌TCP端口号
static int sock_fd=-1, gSocket=-1;
static pthread_t threadId;

int android_sent(uchar *buf, int len)
{
	if(gSocket > 0) {
		len = send(gSocket, buf, len, 0);
        usleep(25*1000);  // 适当延时，等待 移动端数据处理完成
	}
	else
		len = -1;

	return len;
}




/**
 * 功 能：接收数据
 * 参 数：sockfd->套接字，buf->接收数据缓冲区, len-> 接收缓冲区长度
 */
static void tcp_recv(int sockfd)
{
	uchar buf[512] = {0};
	dev_data_packet pkt;
	int ret,rtn;
	do
	{
		ret = recv(sockfd,buf,UDP_BUF_SIZE,0);
		if( ret > 0)
		{

			udp_printf("recv: %d %s\n", ret, buf);

//			rtn = data_packet_analytic(buf, ret, &pkt);
//			if(rtn > 0)
//			{
//				udp_printf("recv: %d %s\n", pkt.len, pkt.data);
//
//
//
//			}
//			else
//				udp_printf("recv err %d\n", ret);
		}
		else
			udp_printf("call to recv err\n");
	}while(ret > 0);

	close(sockfd);
	gSocket = -1;
}

/**
 * 首先进行身份验证
 */
static int landVerify(int sockfd)
{
	char buf[512] = {0};
	int ret = recv(sockfd,buf,UDP_BUF_SIZE,0);
	if(ret > 0) {
		udp_printf("recv land verify : %d %s\n", ret, buf);
		gSocket = sockfd;
		android_sent("OK",2);
	}

	return 1;
}

/**
 * 功 能：接收客户端连接
 *
 */
static int tcp_accept(int sockfd)
{
	struct sockaddr_in pin;

	int size = sizeof(struct sockaddr_in);
	int sock = accept(sockfd,(struct sockaddr *)&pin, &size);
	if(sock >= 0)
	{
		udp_printf("Client IP: %s\n", inet_ntoa(pin.sin_addr));
		if(landVerify(sock) > 0)
			tcp_recv(sock);
	}
    else {
        gSocket = -1;
		udp_printf("call to accept error\n");
        sleep(1);
    }


	return 0;
}

static void tcp_thread_entry(void)
{
	sock_fd = tcp_creatSocket(ANDROID_TCP_PORT, 1);

    while(1) {
		tcp_accept(sock_fd);        
    }

}

/**
 * 创建并启动心跳包线程
 */
void android_tcpServer_thread(void)
{
	pthread_t *id = &threadId;
	int ret = pthread_create(id, NULL, (void *)tcp_thread_entry, NULL);
	if(ret != 0)
		udp_printf("create android tcpServer pthread err\n");
}

/**
 * 终止线程
 */
void android_tcpServer_stop(void)
{
	close(sock_fd);
	pthread_cancel(threadId);
}
