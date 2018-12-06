#ifndef WEBSERVICETHREAD_H
#define WEBSERVICETHREAD_H

#include "websocketclient.h"

class WebServiceThread : public QThread
{
    Q_OBJECT
public:
    explicit WebServiceThread(QObject *parent = nullptr);
    ~WebServiceThread();

protected:
    void run();
    void readDevList();

protected slots:
    void timeoutDone();

protected:
    BuildJson *mBuildJson;
    sDevPackets *mPackets;

    WebSocketClient *mWebSocket;
    QTimer *timer;
    bool isRun;
};

#endif // WEBSERVICETHREAD_H
