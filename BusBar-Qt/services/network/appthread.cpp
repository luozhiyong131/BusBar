#include "appthread.h"
#include "android_tcp_server.h"

AppThread::AppThread(QObject *parent) : QThread(parent)
{

}

AppThread::~AppThread()
{
    android_tcpServer_stop();
}

void AppThread::run()
{
    android_tcpServer_thread();
}
