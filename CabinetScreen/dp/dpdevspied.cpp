#include "dpdevspied.h"
#include "dbalarm.h"

DpDevSpied::DpDevSpied(QObject *parent) : QThread(parent)
{
    isRun = false;
    shm = get_dev_dataPacket(); // 获取共享内存

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
    mTimer->start(1550);
}


/**
 * @brief 定时器启动线程
 */
void DpDevSpied::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

void DpDevSpied::devOffLine(int id)
{
    DbAlarmItem item;
    item.type = tr("PDU离线");
    item.msg = tr("PDU %1 离线").arg(id+1);
    DbAlarm::bulid()->insertItem(item);
    msleep(5);
}

/**
 * @brief 设备状态检查
 */
void DpDevSpied::checkDevState()
{
    for(int i=0; i<DEV_NUM; ++i)
    {
        sDevData *dev = &(shm->dev[i]);
        if((dev->offLine--) > 0)  // 设备必须先在线，然后 才能离线
        {
            if(dev->offLine == 0) {
                devOffLine(i);
            }
        }
    }
}

/**
 * @brief 线程入口函数
 */
void DpDevSpied::run()
{
    if(isRun == false)
    {
        isRun = true;
        checkDevState();

        isRun = false;
    }
}
