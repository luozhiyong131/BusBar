#ifndef BUSTCPSERVER_H
#define BUSTCPSERVER_H

#include <QTcpServer>
#include "tcpsocket.h"

#define ANDROID_TCP_PORT	11283

class BusTcpServer : public QTcpServer
{
public:
    BusTcpServer();

    QByteArray getData();
    bool isConnecting();

signals:

public slots:
    void disconnected();
    void readData(QByteArray str);

private:
    TcpSocket *socket;
    QByteArray mData;

    bool isInconnected;  //判断是否处于正常的tcp连接状态


protected:
    void incomingConnection(int socketDescriptor);
};

#endif // BUSTCPSERVER_H
