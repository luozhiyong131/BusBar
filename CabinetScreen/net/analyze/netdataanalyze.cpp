﻿/*
 * netdataanalyze.cpp
 * 解析网络数据包
 *   此对象会创建UDP接收套接字，接收UDP数据，并创建心跳包对象，广播心跳包
 *
 * 完成的功能
 *      1、自动启动线程，读取UDP队列数据
 *      2、解析数据包：先还原网络数据，再解析设备数据
 *      3、把解析出来的设备数据保存至Hash表中
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "netdataanalyze.h"

#define IP_ADDR     "192.168.1.193"


NetDataAnalyze::NetDataAnalyze(QObject *parent) : QThread(parent)
{
    isRun = true;
    mSocket = new UdpRecvSocket();
    mHeartBeat = new UdpHeartBeat(); //初始化心跳包

    mPacket = new net_data_packet;
    mDevData = new net_dev_data;
    mPduData = new pdu_devData_packet;
    mRecvBuf = (uchar *)malloc(DATA_MSG_SIZE+10);

    QTimer::singleShot(5,this,SLOT(timeoutDone())); //延时初始化
}

NetDataAnalyze::~NetDataAnalyze()
{
    isRun = false;
    wait();

    delete mSocket;
    delete mHeartBeat;
    delete mPacket;
    delete mDevData;
    delete mRecvBuf;
    delete mPduData;
}

/**
 * @brief 创建套接字、启动心跳包发送、自动启动线程接收
 */
void NetDataAnalyze::initFun(void)
{
    start(); // 自动启动线程
}

void NetDataAnalyze::timeoutDone()
{
    initFun();
}


/**
 * @brief 读取接收到的UDP数据、进行解析、保存至Hash中
 * @return
 */
int NetDataAnalyze::recvData(int id, int portNum)
{
    int rtn = mSocket->recvData(id, portNum, mIp, mRecvBuf);
    if(rtn > 0)
    {
        rtn = net_data_analytic(mRecvBuf, rtn, mPacket); //网络数据包解包
        if(rtn > 0) // 正常解析数据包
        {
            rtn = mPacket->len;
            if(rtn>0) //数据长度大于0
            {
                rtn = dev_data_analytic(mPacket->data,rtn, mDevData); // 解析设备数据
                if(rtn>0) /*获取到完整的设备数据包*/
                {
                    mPduData->ip = mIp;
                    mPduData->code = &mPacket->code;
                    mPduData->data = mDevData;
                    pdu_hashData_save(mPduData, id); // 进行数据的保存

                    qDebug() << "#######" << rtn;


                } else
                    qDebug() << "dev data analytic err";
            } else
                qDebug() << "Net Data len err";
        } else
            qDebug() << "Net Data Analyze err" << rtn << id;
    }

    return rtn;
}

void NetDataAnalyze::run(void)
{
    int rtn = 0;
    while (isRun)
    {
        for(int i=0; i<IF_ETH_NUM; ++i) {
            mHeartBeat->heartbeatPacket(i, IP_ADDR);
            msleep(1500);

            qDebug() <<"AAAAAAAAAA";

            for(int k=0; k<UDP_PORT_NUM; k++) {
                do {
                    rtn = recvData(i, k);
                } while(rtn >0);
            }
        }
    }
}
