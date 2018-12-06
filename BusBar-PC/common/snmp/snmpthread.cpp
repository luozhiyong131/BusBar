/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "snmpthread.h"
#include <cassert>

SnmpThread::SnmpThread(QObject *parent) : QThread(parent)
{
    mCount = 0;
    isRun = false;
    mItem = nullptr;
    mPackets = nullptr;
    mOidSubIndex = mId = 0;
    mMutex = new QMutex();

    m_snmp_client =  new QtSnmpClient(this);
    m_snmp_client->setCommunity( "public" );
    connect( m_snmp_client,SIGNAL(responseReceived(qint32,QtSnmpDataList)), this, SLOT(onResponseReceived(qint32,QtSnmpDataList)) );
    connect( m_snmp_client, SIGNAL(requestFailed(qint32)), this, SLOT(onRequestFailed(qint32)) );

    m_timer =  new QTimer(this);
    connect( m_timer, SIGNAL(timeout()), SLOT(makeRequest()) );

    timer =  new QTimer(this);
    timer->start(100);
    connect( timer, SIGNAL(timeout()), SLOT(setSlot()) );

}

SnmpThread::~SnmpThread()
{
    isRun = false;
    wait();
}

void SnmpThread::startRun()
{
    int msec = 0;
    QString addr = "192.168.1.163";
    if(mItem) {
        addr = mItem->ip;
        msec = mItem->msecs * 100;
    }

    m_address = addr;    
    if(isRun) if(m_address == addr) return;
    m_snmp_client->setAgentAddress(QHostAddress(addr));

    if(msec == 0) msec = 500 + (rand() % 1000);
    m_timer->start(msec);

    makeRequest();
    clearCount();
    start();
}

void SnmpThread::stopRun()
{
    m_timer->stop();
    isRun = false;
}


qint32 SnmpThread::setValue(const sSnmpSetCmd &cmd)
{
    if(!m_address.isEmpty()) {
        mSetCmdList.append(cmd);
    }

    return m_address.size();
}


void SnmpThread::setSlot()
{
    if(mSetCmdList.size())
    {
        if( ! m_snmp_client->isBusy() ) {
            sSnmpSetCmd cmd = mSetCmdList.first();
            m_snmp_client->setValue("private", cmd.oid, cmd.type, cmd.value);
            mSetCmdList.removeFirst();
        }
    }
}


void SnmpThread::onResponseReceived(const qint32, const QtSnmpDataList& values )
{
    QMutexLocker locker(mMutex);
    mValues << values;
    sentOkCmd();

//    for( const auto& value : values ) {
//        qDebug( "%s | %s : %s\n", qPrintable( m_address ),  qPrintable( value.address() ),  qPrintable( value.data()) );
//    }
}

void SnmpThread::onRequestFailed( const qint32 request_id ) {
    qDebug() << m_address << request_id;
    saveErrCmd();
}


bool SnmpThread::requestValues(int id)
{
    bool ret = false;
    if( ! m_snmp_client->isBusy() ) {
        QStringList oid = getRequestValues(id);
        if(oid.size()) {
            m_snmp_client->requestValues(oid);
            ret = true;
        }
    }

    return ret;
}

bool SnmpThread::requestSubValues(int id)
{
    bool ret = false;

    if(mOidSubIndex < mOidSubList.size()) {
        if( ! m_snmp_client->isBusy() ) {
            m_snmp_client->requestSubValues( mOidSubList.at(mOidSubIndex++));
        }
    } else {
        mOidSubIndex = 0;
        mOidSubList.clear();
        int rtn = getRequestSubValues(id, mOidSubList);
        if(rtn) {
            ret = true;
            if(rtn > 5) m_timer->start(150);
        }
    }

    return ret;
}

void SnmpThread::setAllOffLine()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            packet->offLine = 0;
        }
    }
}

void SnmpThread::setOffLine()
{
    if(mPackets) {
        mCount += m_timer->remainingTime();//必须大于1秒才执行离线减1
        if(mCount < 1000) return;
        else mCount = 0;

        if(mDataPacket->offLine) mDataPacket->offLine--;
    }
}

void SnmpThread::clearCount()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            memset(&(packet->rtuCount), 0, sizeof(sRtuCount));
        }
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void SnmpThread::sentOkCmd()
{
    if(mPackets) {
        mDataPacket->offLine = 10;
        sRtuCount *count = &(mDataPacket->rtuCount);
        count->count++;
        count->okCount ++;
    }
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void SnmpThread::saveErrCmd()
{
    if(mPackets) {
        sRtuCount *count = &(mDataPacket->rtuCount);
        count->count += 1;
        count->errCount += 1;
    }
}


void SnmpThread::makeRequest()
{
    if(mPackets && isRun) {
        bool ret = requestSubValues(++mId);
        if(!ret) {
            ret = requestValues(mId);
        }
        if(ret) {
            mDataPacket = &(mPackets->dev[mId]);
        }

        if(mId >= mPackets->devNum) {
            mId = 0;
        }

        setOffLine();
    }
}

void SnmpThread::run()
{
    isRun = true;
    while(isRun)
    {
        msleep(10);
        QMutexLocker locker(mMutex);
        for( const auto& value : mValues ) {
            workDown(m_address, value.address(), value.data());
        }
        mValues.clear();
    }
    msleep(200);
    setAllOffLine();
}
