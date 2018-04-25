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
        msleep(865);

    }
}

void ThirdThread::transData()
{
    uchar *buf = mBuf;
    int rtn = mSerial->recvData(buf, 5); //接收数据-
    if(rtn > 0) {
        buf = mBuf;
        mThr->addr = *(buf++);

        mThr->fn   = *buf++;
        mThr->position = (*buf++)<<8 + (*buf++);
        mThr->len = (*buf++)<<8 + (*buf++);
        mThr->crc = (*buf++) + (*buf++)<<8;

        uchar id = mThr->addr % 64;
        uchar addr = mThr->addr % 4;
        if(id >BUS_NUM || addr > BOX_NUM) return;
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        sSrcData *srcData = &(shm->srcData[id]);
        uchar *srcArray = srcData->array[addr];
        uchar len  = srcData->len[addr];
        mSerial->sendData(srcArray, len);
        qDebug() << "**********buf" << QByteArray((char*)mBuf, rtn).toHex();
    }else{
       // qDebug() << "get Ro" << rtn;
    }
}
