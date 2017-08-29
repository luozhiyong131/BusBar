#include "tcpserverthread.h"
#include "tcpserver.h"

TcpServerThread::TcpServerThread(QObject *parent) : QThread(parent)
{

}

TcpServerThread::~TcpServerThread()
{
    tcp_server_stop();
}

void TcpServerThread::run()
{
    tcp_server_thread();
}
