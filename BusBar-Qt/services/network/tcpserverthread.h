#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include "appthread.h"

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpServerThread(QObject *parent = nullptr);
    ~TcpServerThread();

protected:
    void run();

signals:

public slots:
};

#endif // TCPSERVERTHREAD_H
