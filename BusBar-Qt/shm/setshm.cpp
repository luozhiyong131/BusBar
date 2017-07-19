#include "setshm.h"

SetShm::SetShm(QObject *parent) : QObject(parent)
{
    shm = get_share_mem(); // 获取共享内存
}

void SetShm::setThresholdUnit(int id, DbThresholdItem &item, sDataUnit &unit)
{
    unit.min[id] = item.min;
    unit.max[id] = item.max;
    unit.crMin[id] = item.crmin;
    unit.crMax[id] = item.crmax;
}


void SetShm::setLoopCurAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<3; ++k) {
                setThresholdUnit( k, item, box->data.cur);
            }
        }
    }

    DbThreshold::bulid()->setLoopCurAll(item);
}


void SetShm::setLineVolAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = &(shm->data[i]);
        for(int k=0; k<3; ++k)
        {
            setThresholdUnit(k, item, bus->data.vol);
        }
    }
    DbThreshold::bulid()->setLineVolAll(item);
}


void SetShm::setLineCurAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = &(shm->data[i]);
        for(int k=0; k<3; ++k)
        {
            setThresholdUnit(k, item, bus->data.cur);
        }
    }
    DbThreshold::bulid()->setLineCurAll(item);
}

void SetShm::setTempAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = &(shm->data[i]);
        for(int k=0; k<3; ++k)
        {
            setThresholdUnit(k, item, bus->env.tem);
        }
    }

    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<3; ++k) {
                setThresholdUnit( k, item, box->env.tem);
            }
        }
    }
    DbThreshold::bulid()->setTempAll(item);
}

bool SetShm::saveItem(DbThresholdItem &item)
{
    sDataUnit *unit=NULL;
    int boxNum=0, num = item.num;
    sBusData *bus = &(shm->data[item.bus]);
    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度
    {
    case 1:
        unit = &(bus->data.vol);
        break;

    case 2:
        unit = &(bus->data.cur);
        break;

    case 3:
        boxNum = num / 3 + 1;
        num = num % 3 ;
        unit = &(bus->box[boxNum].data.cur);
        break;

    case 4:
         unit = &(bus->env.tem);
        break;

    case 5:
        boxNum = num / 3 + 1;
        num = num % 3 ;
        unit = &(bus->box[boxNum].env.tem);
        break;
    }

    if(unit) {
        setThresholdUnit(num, item, bus->data.cur);
        DbThreshold::bulid()->saveItem(item);
    }
    return true;
}

void SetShm::setName(DbNameItem &item)
{
    char *name = NULL;
    int boxNum=0, num = item.num;
    sBusData *bus = &(shm->data[item.bus]);
    switch(item.type) // 名称类型 1 母线名称   2 插接箱名称
    {
    case 1:
        name = bus->busName;
        break;

    case 2:
        name = bus->box[item.num].boxName;
        break;

    case 3:
        boxNum = num / 3 + 1;
        num = (num-1) % 3 ;
        name = bus->box[boxNum].loopName[num];
        break;
    }

    if(name) {
        QByteArray ba = item.name.toLatin1();
        char *mm = ba.data();
        strcpy(name,mm);
        DbDevName::bulid()->saveItem(item);
    }
}
