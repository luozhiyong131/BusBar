#ifndef UDPRECVSOCKET_H
#define UDPRECVSOCKET_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>

/**
 * UDP层接收到的数据包
 */
typedef struct
{
    QHostAddress addr;
    quint16 port;
    QByteArray datagram;
}UdpBaseData;


class UdpRecvSocket
{
public:
    explicit UdpRecvSocket();
    ~UdpRecvSocket();

    int initSocket(void);
    UdpBaseData *getData(void);

protected:
    bool dataReceived(void);

private:
    QUdpSocket *mUdpSocket;
    QQueue<UdpBaseData*> *mUdpQueueData; // UDP套接字接收数据队列
};

#endif // UDPRECVSOCKET_H
