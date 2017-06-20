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

bool RtuThread::init(const QString& name, int id)
{
    sDataPacket *shm = get_share_mem(); // 获取共享内存
    mBusData = &(shm->data[id]);

    bool ret = mSerial->openSerial(name); // 打开串口
    if(ret)  start(); // 启动线程

    return ret;
}



void RtuThread::outputObjData(sObjData *output, int id, RtuRecvLine *data)
{
    output->vol.value[id] = data->vol;
    output->cur.value[id] = data->cur;

    output->pow[id] = data->pow;
    output->ele[id] = data->ele;
    output->pf[id] = data->pf;
    output->sw[id] = data->sw;
    output->apPow[id] = data->apPow;
    output->ratedCur[id] = data->curAlarm;
}

void RtuThread::outputData(sBoxData *box, Rtu_recv *pkt)
{
    int line=0;
//    for(int k=0; k<3; k++) //========== 不监测分的 所以只有3个
//    {
//        sOutputData *output = &(box->output[k]);
        sObjData *output = &(box->output.data);
        for(int i=0; i<3; i++)
        {
            RtuRecvLine *data = &(pkt->data[line++]);
            outputObjData(output, i, data);
        }
//    }
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
                outputData(box, pkt);
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
        for(int i=1; i<=mBusData->boxNum; ++i)
            transData(i);
    }
}
