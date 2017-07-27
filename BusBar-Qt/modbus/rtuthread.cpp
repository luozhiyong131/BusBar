/*
 * rtuthread.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "rtuthread.h"


RtuThread::RtuThread(QObject *parent) :
    QThread(parent)
{
    mBuf = (uchar *)malloc(RTU_BUF_SIZE);
    mRtuPkt = new Rtu_recv;
    mSerial = new Serial_Trans(this);
}

RtuThread::~RtuThread()
{
    isRun = false;
    wait();
}

/**
 * @brief RTU通讯初始化
 * @param name 串口名
 * @param id 母线ID
 * @return
 */
bool RtuThread::init(const QString& name, int id)
{
    sDataPacket *shm = get_share_mem(); // 获取共享内存
    mBusData = &(shm->data[id-1]);

    bool ret = mSerial->openSerial(name); // 打开串口
    if(ret)
    {
        QTimer::singleShot(3*1000,this,SLOT(start()));  // 启动线程
    }

    return ret;
}



void RtuThread::loopObjData(sObjData *loop, int id, RtuRecvLine *data)
{
    loop->vol.value[id] = data->vol;
    loop->cur.value[id] = data->cur;

    loop->pow[id] = data->pow;
    loop->ele[id] = data->ele;
    loop->pf[id] = data->pf;
    loop->sw[id] = data->sw;
    loop->apPow[id] = data->apPow;
    loop->ratedCur[id] = data->curAlarm;
    loop->wave[id] = data->wave;
}

void RtuThread::loopData(sBoxData *box, Rtu_recv *pkt)
{
    sObjData *loop = &(box->data);
    for(int i=0; i<LINE_NUM; i++)
    {
        RtuRecvLine *data = &(pkt->data[i]);
        loopObjData(loop, i, data);
    }
    loop->lineNum = pkt->lineNum;
}

void RtuThread::envData(sEnvData *env, Rtu_recv *pkt)
{
    for(int i=0; i<SENSOR_NUM; ++i)
    {
        env->tem.value[i] = pkt->env[i].tem;
        env->hum.value[i] = pkt->env[i].hum;
    }
}


void RtuThread::transData(int addr)
{
    char offLine = 0;
    uchar *buf = mBuf;
    Rtu_recv *pkt = mRtuPkt;
    sBoxData *box = &(mBusData->box[addr-1]);

    int rtn = rtu_sent_buff(addr,buf); // 把数据打包成通讯格式的数据
    rtn = mSerial->transmit(buf, rtn, buf); // 传输数据，发送同时接收
    if(rtn > 0) {
        bool ret = rtu_recv_packet(buf, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
                loopData(box, pkt);
                envData(&(box->env), pkt);
            }
        }
    }
    box->offLine = offLine;
}


void RtuThread::run()
{
    isRun = true;
    while(isRun)
    {
//        for(int i=1; i<=mBusData->boxNum; ++i) {
//            transData(i);
            transData(1);
            msleep(1);
//        }
    }
}
