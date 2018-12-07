/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_rtutrans.h"

BUS_RtuTrans::BUS_RtuTrans(QObject *parent) : RtuTrans(parent)
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*ARRAY_SIZE);
    mRecvBuf = (uchar *)malloc(2*ARRAY_SIZE);
    mMutex = new QMutex();

    mRtuPkt = new BUS_RtuRecv();
    mRtuSent = new BUS_RtuSent();
}

BUS_RtuTrans::~BUS_RtuTrans()
{
    isRun = false;
    wait();
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void BUS_RtuTrans::init(SerialPort *serial)
{
    mSerial = serial;
}


bool BUS_RtuTrans::sentCmd(sRtuSentCom &cmd)
{
    bool ret = true;
    mCmdList.append(cmd);

    if(!mSerial) return ret = false;
    return ret;
}

void BUS_RtuTrans::sentCmdList()
{
    if(mCmdList.size() > 0) {
        sRtuSentCom cmd = mCmdList.first();
        bool ret = sentSetCmd(cmd.addr, cmd.reg, cmd.len, 10);
        if(ret) mCmdList.removeFirst();
    }
}

/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
bool BUS_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[ARRAY_SIZE] = {0};
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "bus si sent Set Cmd Err";
        }
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int BUS_RtuTrans::transData(int addr, BUS_RtuRecv *pkt, int msecs)
{
    char offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = bus_rtu_recv_packet(recv, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }

    return offLine;
}

void BUS_RtuTrans::loopObjData(sObjData *loop, BUS_RtuRecvLine *data)
{
    loop->vol.value = data->vol;
    loop->vol.min = data->minVol;
    loop->vol.max = data->maxVol;

    loop->cur.value = data->cur;
    loop->cur.min = data->minCur;
    loop->cur.max = data->maxCur;

    loop->pow = data->pow;
    loop->ele = data->ele;
    loop->pf = data->pf;
    loop->sw = data->sw;
    loop->activePow = data->activePow;
    loop->wave = data->wave;
}

void BUS_RtuTrans::loopData(sDevData *box, BUS_RtuRecv *pkt)
{
    box->loopNum = pkt->lineNum;

    for(int i=0; i<box->loopNum; i++)
    {
        BUS_RtuRecvLine *data = &(pkt->data[i]);
        sObjData *loop = &(box->loop[i]);
        loop->id = i;
        loopObjData(loop, data);
    }
}

void BUS_RtuTrans::envData(sDataPacket *box, BUS_RtuRecv *pkt)
{
    for(int i=0; i<SENOR_NUM; ++i) {
        sDataUnit *env = &(box->data.env.tem[i]);
        env->value = pkt->env[i].tem.value;
        env->min = pkt->env[i].tem.min;
        env->max = pkt->env[i].tem.max;
    }
}


void BUS_RtuTrans::thdData(sDevPackets *packets, BUS_RtuRecv *pkt)
{
    sDataPacket *box = &(packets->dev[pkt->addr]);

    box->lps = pkt->lps;
    for(int i=0; i<LINE_NUM; ++i) {
        box->data.line[i].pl = pkt->pl[i];
    }

    if(pkt->addr == 0) {
        int line = pkt->hc % 3;
        ushort *thd = packets->thd[line].curThd;
        if(pkt->hc < 3) thd = packets->thd[line].volThd;
        for(int i=0; i<BUS_RTU_THD_NUM; ++i) thd[i] = pkt->thd[i];

        if(pkt->hc < 3) {
            box->data.line[line].volThd = thd[0];
        } else {
            box->data.line[line].curThd = thd[0];
        }
        thd[0] = 0;

    } else {
        for(int i=0; i<LINE_NUM; ++i) {
            box->data.line[i].curThd = pkt->thd[i];
        }
    }
}

int BUS_RtuTrans::transmit(int addr, sDevPackets *packets, int msecs)
{
    BUS_RtuRecv *pkt = mRtuPkt; //数据包
    sDataPacket *box = &(packets->dev[addr]);

    sentCmdList();
    int ret = transData(addr, pkt, msecs);
    if(ret) {
        loopData(&(box->data), pkt); //更新数据
        envData(box, pkt);

        box->hz = pkt->rate;
        box->dc = pkt->dc;
        box->version = pkt->version;

        thdData(packets, pkt);
    }
    box->offLine = ret; //在线

    return box->offLine;
}


QByteArray BUS_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > ARRAY_SIZE))  mSentLen = ARRAY_SIZE;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray BUS_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > ARRAY_SIZE))  mRecvLen = ARRAY_SIZE;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
