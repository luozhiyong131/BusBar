/*
 * tcpserver.c
 *
 *  Created on: 2016年8月5日
 *      Author: lzy
 */
#include "tcpserver.h"
#include "netDataSegment.h"

#define TCP_PORT	12707 // TCP端口号
static int sock_fd = -1;
static pthread_t threadId;

/**
 * 功 能： 创套接字
 * 参 数：port->端口，lisnum->等待连接队列的最大长度。
 * 返 回：套接字
 */
int tcp_creatSocket(int port, int lisnum)
{
	int ret;
	struct sockaddr_in sin;//struct sockaddr结构体用来处理网络通信的地址。

	/*
	 *int socket(int domain, int type, int protocol);
	 * PF_INET, AF_INET： Ipv4网络协议
	 * PF_INET6, AF_INET6： Ipv6网络协议。
	 * type参数的作用是设置通信的协议类型，可能的取值如下所示：
	　　      SOCK_STREAM： 提供面向连接的稳定数据传输，即TCP协议。
	　　      OOB： 在所有数据传送前必须使用connect()来建立连接状态。
	　      　SOCK_DGRAM： 使用不连续不可靠的数据包连接。
	　　      SOCK_SEQPACKET： 提供连续可靠的数据包连接。
	　      　SOCK_RAW： 提供原始网络协议存取。
	　      　SOCK_RDM： 提供可靠的数据包连接。
	　　      SOCK_PACKET： 与网络驱动程序直接通信。
	 */
	//socket函数，向系统申请一个通信端口
	int sockfd=socket(AF_INET,SOCK_STREAM,0);//IPV4 TCP协议
	if(sockfd >= 0)//申请失败
	{
		memset(&sin,0,sizeof(sin));// 初始化 然后是设置套接字
		sin.sin_family = AF_INET;//协议族，在socket编程中只能是AF_INET(TCP/IP协议族)
		sin.sin_addr.s_addr=INADDR_ANY;//sin_addr存储IP地址,使用in_addr这个数据结构
		sin.sin_port=htons(port);//存储端口号

		ret = bind(sockfd,(struct sockaddr *)&sin,sizeof(sin)); //将套接字（sin） 跟端口（sockfd）链接
		if(ret >= 0)
		{
			/*int PASCAL FAR listen( SOCKET s, int backlog);
			　　     S：用于标识一个已捆绑未连接套接口的描述字。
			　　     backlog：等待连接队列的最大长度。
			 * listen()仅适用于支持连接的套接口，如SOCK_STREAM类型的。
			 */
			ret = listen(sockfd,lisnum);
			if(ret >= 0) //在端口sockfd监听
			{
				udp_printf("TCP accepting connections \n");
				return sockfd;;
			}
			else
				udp_printf("call to listen err\n");
		}
		else
			udp_printf("call to bind\n");
	}
	else
		udp_printf("call to socket err");

	return -1;
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
			rtn = data_packet_analytic(buf, ret, &pkt);
			if(rtn > 0)
			{
				udp_printf("recv: %d %s\n", pkt.len, pkt.data);

//				for(int i=0; i< pkt.len; ++i) {
//					udp_printf("%x ", pkt.data[i]);
//				}


			}
			else
				udp_printf("recv err %d\n", ret);
		}
		else
			udp_printf("call to recv err\n");
	}while(ret > 0);

	close(sockfd);
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
		/*int PASCAL FAR recv( SOCKET s, char FAR* buf, int len, int flags);
			　　        s：一个标识已连接套接口的描述字。
			　　        buf：用于接收数据的缓冲区。
			　　        len：缓冲区长度。
			　　        flags：指定调用方式。
		 */

		udp_printf("Client IP: %s\n", inet_ntoa(pin.sin_addr));
		tcp_recv(sock);
	}
	else
		udp_printf("call to accept error\n");

	return 0;
}

static void tcp_thread_entry(void)
{
	sock_fd = tcp_creatSocket(TCP_PORT, 20);

	while(1)
		tcp_accept(sock_fd);

}



/**
 * 创建并启动心跳包线程
 */
void tcp_server_thread(void)
{
	pthread_t *id = &threadId;
	int ret = pthread_create(id, NULL, (void *)tcp_thread_entry, NULL);
	if(ret != 0)
		udp_printf("create hb pthread err\n");
}

/**
 * 终止线程
 */
void tcp_server_stop(void)
{
	close(sock_fd);
	pthread_cancel(threadId);
}










