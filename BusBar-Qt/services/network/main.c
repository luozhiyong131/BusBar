
#include "devDataSent.h"
#include "tcpserver.h"
#include "android_tcp_server.h"

int main(int argc, char **argv)
{
	udp_hb_thread(); // 创建心跳包线程
	tcp_server_thread();
	android_tcpServer_thread();

	int lzy = 100;
	while(lzy)
	{
		sent_test();
		sleep(1);
	}
	udp_hb_stop(); // 停止心中包线程
	tcp_server_stop();
	android_tcpServer_stop();

	return 0;
}


