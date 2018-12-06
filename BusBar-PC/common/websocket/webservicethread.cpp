#include "webservicethread.h"

WebServiceThread::WebServiceThread(QObject *parent) : QThread(parent)
{
    mBuildJson = NULL;
    mPackets = NULL;
    mWebSocket = new WebSocketClient(this);

    isRun = false;
    timer = new QTimer(this);
//    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


WebServiceThread::~WebServiceThread()
{
    isRun = false;
    wait();
}

void WebServiceThread::readDevList()
{
    if(mPackets) {
        for(int i=0; i<mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            if(packet->offLine > 0)  // 必须在线才进行检查
            {
                QJsonObject json;
                bool ret = mBuildJson->getJson(packet, json);
                if(ret) {
                    ret = mWebSocket->sendMessage(json);
//                    mBuildJson->saveJson("saveTest", json);
                }
            }

            if(!isRun)   return;

            // if(isRun) msleep(10); // 延时1us 让其它线程优先执行
            // else return;
        }
    }
}

void WebServiceThread::timeoutDone()
{
    if(!isRun) run(); //start();
}

void WebServiceThread::run()
{
    if(!isRun) {
        isRun = true;
        readDevList();
        isRun = false;
    }
}
