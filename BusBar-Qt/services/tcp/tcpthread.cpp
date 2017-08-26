#include "tcpthread.h"

static bool landVerify(QByteArray array);

TcpThread::TcpThread(QObject *parent)
{
    is_run = false;
    mServer = new BusTcpServer;

    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutdone()));
    timer->start(5*1000);
}

void TcpThread::run()
{
    if(is_run == false)
    {
        is_run  = true;
        QByteArray array = mServer->getData();
        bool ret = landVerify(array);
        if(ret == true)


        is_run  = false;
    }

}

bool landVerify(QByteArray array)
{
    QString str = QString(array);
    if(str == "admin; admin; 0")
        return true;
    return false;
}


void TcpThread::timeoutdone()
{
    if(!is_run)
    {
        start();
    }
}

