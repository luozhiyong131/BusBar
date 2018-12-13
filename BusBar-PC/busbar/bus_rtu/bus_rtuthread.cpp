#include "bus_rtuthread.h"

BUS_RtuTrans *g_RtuTrans[4] = {nullptr, nullptr, nullptr, nullptr};

BUS_RtuThread::BUS_RtuThread(QObject *parent) : RtuThread(parent)
{
    init(0);
    mRtu = new BUS_RtuTrans(this);
}

void BUS_RtuThread::init(int id)
{
    mBusId=id;
    g_RtuTrans[id] = mRtu;
}


void BUS_RtuThread::initSlot()
{
    int id = mBusId;
    SerialPort *serial = BUS_ConfigFile::bulid()->mItem->serials[id];
    mPackets = BUS_DataPackets::bulid()->getBus(id);

    if(serial) {
        mRtu->init(serial);
    } else {
        QTimer::singleShot(1400,this,SLOT(initSlot()));
    }
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void BUS_RtuThread::writeErrCmd(int id)
{
    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);

    strArray += tr(" (接收数据");
    array = mRtu->getRecvCmd();
    strArray += " len=" +QString::number(array.size()) +": ";
    strArray += cm_ByteArrayToHexStr(array);
    strArray += ")";

    QStringList list;
    list << QString::number(id);
    list << strArray;

//    BUS_DpThread::bulid(this)->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void BUS_RtuThread::workDown()
{
    int ret = 0;

    int id = mBusId;
    BUS_sConfigItem *item = BUS_ConfigFile::bulid()->mItem;
    mPackets->devNum = item->devNums[id];

    for(int k=0; k<=mPackets->devNum; ++k)
    {
        for(int j=0; j<item->cmdModel; ++j) { // 双命令模式
            ret = mRtu->transmit(k, mPackets, item->msecs);
            if(ret) break;
        }

        sDataPacket *box = &(mPackets->dev[k]);
        if(ret) { // 正常收到数据
            sentOkCmd(box->rtuCount);
        } else { // 数据异常
            saveErrCmd(k, box->rtuCount);
        }

        if(isRun) msleep(755);
        else return;
    }
}
