/*
 * rtuthread.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "rtuthread.h"

static ushort gBoxArray[4] = {0, 0, 0, 0};

void set_box_num(int id, int num)
{
    gBoxArray[id] = num;
}



RtuThread::RtuThread(QObject *parent) :
    QThread(parent)
{
    mBuf = (uchar *)malloc(RTU_BUF_SIZE); //申请内存  -- 随便用
    mRtuPkt = new Rtu_recv; //传输数据结构
    mSerial = new Serial_Trans(this); //串口线程
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
    if(ret) {
        QTimer::singleShot(3*1000,this,SLOT(start()));  // 启动线程
    }

    mId = id-1;

    return ret;
}

int RtuThread::transmit(int addr, ushort reg, ushort len)
{
    /*
     *  0 - 发送失败
     *  1 - 发送完成
     * -1 - 不在线
     * -2 - 发送却没收到
     */
    //判断是否在线
    sBoxData *box = &(mBusData->box[addr]); //共享内存
    if(box->offLine == 0){ //不在线
        return -1;
    }
    //打包数据
    uchar *buf = mBuf;
    uchar *get = mBuf + 20;
    int rtn = rtu_sent_buff(addr, reg, len, buf); // 把数据打包成通讯格式的数据
    rtn = mSerial->transmit(buf, rtn, get); //发送并回收
    if(rtn > 0){ //回收到数据
        for(int i = 0; i < rtn; i++){
            if(*buf++ != *get++) return 0;
        }
        return 1;
    }
    return -2;

}

int RtuThread::sendData(int addr, ushort reg, ushort len, bool value)
{   
    if(addr == 0xFF){
        uchar *buf = mBuf;
        int rtn = rtu_sent_buff(addr, reg, len, buf); // 把数据打包成通讯格式的数据
        return mSerial->sendData(buf, rtn, 800); //发送 -- 并占用串口800ms
    }else{
        sBoxData *box = &(mBusData->box[addr]); //共享内存
        if((box->offLine > 0) || value){ //在线
            //打包数据
            uchar *buf = mBuf;
            int rtn = rtu_sent_buff(addr, reg, len, buf); // 把数据打包成通讯格式的数据
            return mSerial->sendData(buf, rtn, 800); //发送 -- 并占用串口800ms
        }
    }
    return -1;
}

int RtuThread::sendData(uchar *pBuff, int nCount, int msec)
{
    return mSerial->sendData(pBuff, nCount, msec);
}

void RtuThread::setBoxNum(ushort num)
{
    sendData(0, 0x1040, num, false);
}

void RtuThread::loopObjData(sObjData *loop, int id, RtuRecvLine *data)
{
    loop->vol.value[id] = data->vol;
    loop->vol.crMin[id] = loop->vol.min[id] = data->minVol;
    loop->vol.crMax[id] = loop->vol.max[id] = data->maxVol;

    loop->cur.value[id] = data->cur;
    loop->cur.crMin[id] = loop->cur.min[id] = data->minCur;
    loop->cur.crMax[id] = loop->cur.max[id] = data->maxCur;

    loop->pow[id] = data->pow;
    loop->ele[id] = data->ele;
    loop->pf[id] = data->pf;
    loop->sw[id] = data->sw;
    loop->apPow[id] = data->apPow;
    //    loop->ratedCur[id] = data->curAlarm; ////

    loop->wave[id] = data->wave;
}

void RtuThread::loopData(sBoxData *box, Rtu_recv *pkt)
{
    sObjData *loop = &(box->data);
    box->loopNum = loop->lineNum = pkt->lineNum;

    for(int i=0; i<loop->lineNum; i++)
    {
        RtuRecvLine *data = &(pkt->data[i]);
        loopObjData(loop, i, data);
    }
}

void RtuThread::envData(sEnvData *env, Rtu_recv *pkt)
{
    for(int i=0; i<SENSOR_NUM; ++i)
    {
        env->tem.value[i] = pkt->env[i].tem.value;
        env->tem.crMin[i] = env->tem.min[i] = pkt->env[i].tem.min;
        env->tem.crMax[i] = env->tem.max[i] = pkt->env[i].tem.max;

        env->hum.value[i] = pkt->env[i].hum.value;
    }
}

void RtuThread::thdData(Rtu_recv *pkt)
{
    sBoxData *box = &(mBusData->box[pkt->addr]);

    box->lps = pkt->lps;
    for(int i=0; i<3; ++i) {
        box->data.pl[i] = pkt->pl[i];
    }

    if(pkt->addr == 0) {
        int line = pkt->hc % 3;
        ushort *thd = mBusData->thdData.curThd[line];
        if(pkt->hc < 3) thd = mBusData->thdData.volThd[line];
        for(int i=0; i<32; ++i) thd[i] = pkt->thd[i];

        if(pkt->hc < 3) {
            box->data.volThd[line] = mBusData->thdData.volThd[line][0];
            mBusData->thdData.volThd[line][0] = 0;
        } else {
            box->data.curThd[line] = mBusData->thdData.curThd[line][0];
            mBusData->thdData.curThd[line][0] = 0;
        }

    } else {
        int *thd = box->data.curThd;
        for(int i=0; i<3; ++i) {
            thd[i] = pkt->thd[i];
        }
    }
}

int RtuThread::transData(int addr)
{
    char offLine = 0;
    uchar *buf = mBuf;
    Rtu_recv *pkt = mRtuPkt; //数据包
    sBoxData *box = &(mBusData->box[addr]); //共享内存

    int rtn = rtu_sent_buff(addr,buf); // 把数据打包成通讯格式的数据
    rtn = mSerial->transmit(buf, rtn, buf); // 传输数据，发送同时接收
    if(rtn > 0) {
        bool ret = rtu_recv_packet(buf, rtn, pkt); // 解析数据 data - len - it
        if(ret) {
            if(addr == pkt->addr) { //回收地址和发送地址同
                offLine = 2;
                loopData(box, pkt); //更新数据
                envData(&(box->env), pkt);
                box->rate = pkt->rate;
                box->dc = pkt->dc;
                box->version = pkt->version;

                thdData(pkt);
            }

            box->rtuLen = rtn;
            for(int i = 0; i < rtn; i++){
                box->rtuArray[i] = buf[i];
            }
        }else{
            box->rtuLen = 0;  //数据出错清零
        }
    }

    if(offLine) {
        box->offLine = offLine; //在线
    } else {
        if(box->offLine > 0)
            box->offLine--;
    }

    return offLine;
}


void RtuThread::run()
{
    isRun = true;
    while(isRun)
    {
        ushort num = gBoxArray[mId];
        if(num) {
            setBoxNum(num);
            gBoxArray[mId] = 0;
        }

        for(int i=0; i<=mBusData->boxNum; ++i)
        {
            if(transData(i) == 0 ) {
                transData(i);
            }
            msleep(750);
        }
    }
}
