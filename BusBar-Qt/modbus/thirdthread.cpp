#include "thirdthread.h"

ThirdThread::ThirdThread(QObject *parent)
    : QThread(parent)
{
    mBuf = (uchar *)malloc(RTU_BUF_SIZE); //申请内存  -- 随便用
    mThr = new ThrData;
    mSerial = new Serial_Trans(this); //串口线程
}

bool ThirdThread::init(const QString &name)
{
    bool ret = mSerial->openSerial(name); // 打开串口
    if(ret)
    {
        QTimer::singleShot(3*1000,this,SLOT(start()));  // 启动线程
    }
    return ret;
}

void ThirdThread::run()
{
    isRun = true;
    while(isRun)
    {
        transData();
        msleep(200);
    }
}

void ThirdThread::transData()
{
    uchar *buf = mBuf;
    int rtn = mSerial->recvData(buf, 5); //接收数据-
    if(rtn > 0 ) {
        if(!validateData(rtn)) return; //解析并验证数据
        uchar id = mThr->addr % 64;
        uchar addr = mThr->addr % 4;
        if(id >=BUS_NUM || addr >= BOX_NUM || mThr->fn != 3) return;
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        sSrcData *srcData = &(shm->srcData[id]);
        uchar *srcArray = srcData->array[addr];
        uchar len  = srcData->len[addr];
        mSerial->sendData(srcArray, len);
        qDebug() << "len:" << len;
        qDebug() << "**********buf" << QByteArray((char*)mBuf, rtn).toHex();
    }else{
       // qDebug() << "get Ro" << rtn;
    }
}

bool ThirdThread::validateData(int rtn)
{
    uchar *buf = mBuf;
    buf = mBuf;
    mThr->addr = *(buf++);
    mThr->fn   = *buf++;
    ushort ll, hh;
    hh = *buf++;
    ll = *buf++;
    mThr->position = hh<<8 + ll;
    hh = *buf++;
    ll = *buf++;
    mThr->len = hh<<8 + ll;
    ll = *buf++;
    hh = *buf++;
    mThr->crc = (ll<<8) + hh;
    buf = mBuf;
    ushort hlcrc = rtu_crc(buf, rtn-2);
    ushort lhcrc = (hlcrc >> 8) + (hlcrc<<8);
    if(mThr->crc != lhcrc ) return false;
    return true;
}
