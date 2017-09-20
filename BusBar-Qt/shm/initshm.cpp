#include "initshm.h"
#include "dbthreshold.h"
#include "dbdevname.h"

InitShm::InitShm(QObject *parent) : QThread(parent)
{
    shm = get_share_mem(); // 获取共享内存
}

/**
 * @brief 初始化插接箱数量
 */
void InitShm::initBoxNum()
{
    for(int i=0; i<BUS_NUM; ++i) {
        int boxNum = getBoxNum(i);
        if(boxNum <= 0) boxNum = 18;
        shm->data[i].boxNum = boxNum; // 18个插接箱

        int rateCur = getRateCur(i);
        if(rateCur <= 0) rateCur = 2600;
        shm->data[i].ratedCur = rateCur;
    }
}

void InitShm::initThresholdUnit(int bus, int type, int num, int id, sDataUnit &unit, int max)
{
    DbThresholdItem item;
    item.bus = bus;
    item.type = type;
    item.num = num;

    bool ret = DbThreshold::bulid()->getItem(item);
    if(ret) {
        unit.min[id] = item.min;
        unit.max[id] = item.max;
        unit.crMin[id] = item.crmin;
        unit.crMax[id] = item.crmax;
    } else {
        unit.max[id] = max;
        unit.crMax[id] = max;

        item.min = 0;
        item.max = max;
        item.crmin = 0;
        item.crmax = max;
        DbThreshold::bulid()->saveItem(item);
    }
}

void InitShm::initThresholdUnit(int bus, int type, int num, sDataUnit &unit, int max)
{
    initThresholdUnit(bus, type, num, num, unit, max);
}

void InitShm::initBoxThreshold()
{    
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<LINE_NUM; ++k)
            {
                int num = (j-1)*LINE_NUM + k; // 回路编号规划
                initThresholdUnit(i, 3, num, k, box->data.cur, 320);
                num++;
            }

            for(int k=0; k<SENSOR_NUM; ++k)
            {
                int num = (j-1)*SENSOR_NUM + k; // 回路编号规划
                initThresholdUnit(i, 5, num, k, box->env.tem, 99);
                num++;
            }
        }
    }
}

void InitShm::initBusThreshold()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = &(shm->data[i]);
        for(int k=0; k<3; ++k)
        {
            initThresholdUnit(i, 1, k, bus->data.vol, 255);
            initThresholdUnit(i, 2, k, bus->data.cur, 1000);
            initThresholdUnit(i, 4, k, bus->env.tem, 99);
        }
    }
}

void InitShm::initThreshold()
{
    initBusThreshold();
    initBoxThreshold();
}

void InitShm::initNameUnit(int bus, int type, int num, char *buf, const QString &name)
{
    QString  str = DbDevName::bulid()->getName(bus, type, num);
    if(str.isEmpty())
    {
        DbNameItem item;
        item.bus = bus;
        item.type = type;
        item.num = num;
        item.name = name;
        DbDevName::bulid()->saveItem(item);
        str = name;
    }

    QByteArray ba = str.toLatin1();
    char *mm = ba.data();
    strcpy(buf,mm);
}


void InitShm::initBusName()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        initNameUnit(i, 1, 0, busData->busName, QString("bus-%1").arg(i+1));
    }
}

void InitShm::initBoxName()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<BOX_NUM/*busData->boxNum*/; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            initNameUnit(i, 2, j, box->boxName, QString("iBox-%1").arg(j));
        }
    }
}

void InitShm::initLoopName()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<LINE_NUM; ++k) {
                char *loop = box->loopName[k];
                int num = j*LINE_NUM + k;
                initNameUnit(i, 3, num, loop, QString("loop-%1").arg(k+1));
            }
        }
    }
}

void InitShm::initName()
{
    initBusName();
    initBoxName();
    initLoopName();
}

void InitShm::run()
{
    initBoxNum();
    initName();
    initThreshold();
}
