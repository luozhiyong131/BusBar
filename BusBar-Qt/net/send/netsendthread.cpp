#include "netsendthread.h"
#include "devDataSent.h"
#include "apptcpserver.h"
#include "send/devsetthread.h"

NetSendThread::NetSendThread(QObject *parent) : QThread(parent)
{
    AppTcpServer::bulid()->start();
    DevSetThread::bulid()->start();
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
        sent_dev_data();
        sleep(1);       
    }
}
