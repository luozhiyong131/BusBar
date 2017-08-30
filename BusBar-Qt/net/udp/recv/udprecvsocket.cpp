/*
 * UdpRecvSocket.cpp
 * UDP 接收套接字
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "udprecvsocket.h"
#define UDP_RECV_PORT  28720  /* 接收套接字起始端口 */
static int g_port = 0;


/**
 * @brief 构造函数
 * @param parent
 */
UdpRecvSocket::UdpRecvSocket()
{
    mUdpSocket = NULL;
    mUdpQueueData = new QQueue<UdpBaseData*>();
}

UdpRecvSocket::~UdpRecvSocket()
{
    delete mUdpSocket;
    delete mUdpQueueData;
}

/**
 * @brief 初始化套接字
 * @return 端口号
 */
int UdpRecvSocket::initSocket(void)
{
    bool ret = true;
    int port = -1;

    mUdpSocket = new QUdpSocket(0);
    do
    {
        port = UDP_RECV_PORT + g_port++;
        ret = mUdpSocket->bind(port  /*, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint*/); //此处的bind是个重载函数，连接本机的port端口，采用ShareAddress模式(即允许其它的服务连接到相同的地址和端口，特别是 用在多客户端监听同一个服务器端口等时特别有效)，和ReuseAddressHint模式(重新连接服务器)
        if(ret)
        {
            // connect(g_udpSocket,SIGNAL(readyRead()),this,SLOT(dataReceivedSlot())); // 数据接收
            break; //退出
        }
        else
            qDebug() << "udp socket create err" << port;
    } while(ret == false);

    return port;
}



/**
 * @brief 获取UDP数据包
 * @param data
 * @return
 */
UdpBaseData *UdpRecvSocket::getData(void)
{
    UdpBaseData *data = NULL;

    dataReceived();
    int ret = mUdpQueueData->size();
    if( ret > 0)
        data = mUdpQueueData->dequeue();

    return data;
}




/**
 * @brief 读取socket数据
 * @return
 */
bool UdpRecvSocket::dataReceived(void)
{   
    if(mUdpSocket->hasPendingDatagrams()) // 是否有数据可读
    {
        UdpBaseData *data = new UdpBaseData();
        if(data) {
            data->datagram.resize(mUdpSocket->pendingDatagramSize()); //让datagram 的大小为等待处理的数据报的大小，这样才能接收到完整的数据

            int rtn = mUdpSocket->readDatagram(data->datagram.data(),
                                               data->datagram.size(),
                                               &data->addr,
                                               &data->port);
            if(rtn > 0)
            {
                if(data->datagram.size() < 1024) /*数据最长不超过1024*/
                {
                    mUdpQueueData->enqueue(data);
                }
            }
        } else {
            qDebug() << "new UdpBaseData err";
        }
    }

    return mUdpSocket->hasPendingDatagrams();
}


