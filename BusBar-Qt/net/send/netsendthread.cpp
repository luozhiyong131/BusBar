#include "netsendthread.h"
#include "devDataSent.h"
#include "apptcpserver.h"

NetSendThread::NetSendThread(QObject *parent) : QThread(parent)
{
    AppTcpServer::bulid()->start();
}

NetSendThread *NetSendThread::bulid()
{
    static NetSendThread* sington = NULL;
    if(sington == NULL)
        sington = new NetSendThread();
    return sington;
}

void NetSendThread::run()
{
    while (1) {
        sent_test();
        sleep(1);
    }
}
