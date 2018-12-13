#include "bus_setshm.h"

BUS_SetShm::BUS_SetShm(QObject *parent) : QObject(parent)
{
    shm = BUS_DataPackets::bulid(); // 获取共享内存
}

void BUS_SetShm::setThresholdUnit(sThresholdItem &item, sDataUnit *unit)
{
    unit->min = item.min;
    unit->max = item.max;
    unit->crMin = item.crmin;
    unit->crMax = item.crmax;
}

void BUS_SetShm::setVolAll(sThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sDevPackets *busData = shm->getBus(i);
        for(int j=0; j<=busData->devNum; ++j)
        {
            sDataPacket *box = &(busData->dev[j]);
            for(int k=0; k<LOOP_NUM; ++k) {
                sDataUnit *unit = &(box->data.loop[k].vol);
                setThresholdUnit(item, unit);
            }
        }
    }
}

void BUS_SetShm::setLoopCurAll(sThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sDevPackets *busData = shm->getBus(i);
        for(int j=1; j<=busData->devNum; ++j)
        {
            sDataPacket *box = &(busData->dev[j]);
            for(int k=0; k<LOOP_NUM; ++k) {
                sDataUnit *unit = &(box->data.loop[k].cur);
                setThresholdUnit(item, unit);
            }
        }
    }
}

void BUS_SetShm::setLineCurAll(sThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sDevPackets *busData = shm->getBus(i);
        for(int k=0; k<LINE_NUM; ++k) {
            sDataUnit *unit = &(busData->dev[0].data.loop[k].cur);
            setThresholdUnit(item, unit);
        }
    }
}

void BUS_SetShm::setLineTempAll(sThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sDevPackets *busData = shm->getBus(i);
        for(int k=0; k<SENOR_NUM; ++k) {
            sDataUnit *unit = &(busData->dev[0].data.env.tem[k]);
            setThresholdUnit(item, unit);
        }
    }
}

void BUS_SetShm::setLoopTempAll(sThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sDevPackets *busData = shm->getBus(i);
        for(int j=1; j<=busData->devNum; ++j)
        {
            sDataPacket *box = &(busData->dev[j]);
            for(int k=0; k<SENOR_NUM; ++k) {
                sDataUnit *unit = &(box->data.env.tem[k]);
                setThresholdUnit(item, unit);
            }
        }
    }
}

void BUS_SetShm::saveItem(sThresholdItem &item)
{
    sDataUnit *unit=NULL;

    sDevPackets *bus = shm->getBus(item.bus);
    sObjData *box = &(bus->dev[item.box].data.loop[item.num]);
    switch(item.type) // 阈值类型 1 电压阈值  2 电流阈值 3 温度
    {
    case 1: unit = &(box->vol); break;
    case 2: unit = &(box->cur); break;
    case 3: unit = &(bus->dev[item.box].data.env.tem[item.num]); break;
    }

    if(unit) {
        setThresholdUnit(item, unit);
    }

}

void BUS_SetShm::setItem(sThresholdItem &item)
{
    if(item.box == 0xFF) {
        switch (item.type) {
        case 1:  setVolAll(item); break;
        case 2:  setLoopCurAll(item); break;
        case 3:  setLoopTempAll(item); break;
        }
    } else if(item.bus == 0xFF) {
        switch (item.type) {
        case 1:  setVolAll(item); break;
        case 2:  setLineCurAll(item); break;
        case 3:  setLineTempAll(item); break;
        }
    }else {
        saveItem(item);
    }
}

void BUS_SetShm::setName(DbNameItem &item)
{
    char *name = NULL;
    sDataPacket *box = shm->getBox(item.bus, item.box);
    switch(item.type) // 名称类型 1 母线名称   2 插接箱名称
    {
    case 1: name = box->name; break;
    case 2: name = box->name; break;
    case 3: name = box->data.loop[item.num].name;break;
    }

    if(name) {
        QByteArray ba = item.name.toLatin1();
        char *mm = ba.data();
        strcpy(name,mm);
        BUS_DbName::bulid()->saveItem(item);
    }
}

/**
 * @brief SetShm::setLineRatedCur  设置母线额定电流
 * @param index  母线编号
 * @param data   额定电流值
 */
void BUS_SetShm::setRatedCur(int index, int data)
{
    shm->getBox(index, 0)->ratedCur = data;
    QString str = QString::number(data,10);
    QString name = QString("bus_rateCur_%1").arg(index+1);
    sys_configFile_writeParam(name,str);
}

/**
 * @brief SetShm::setLineBoxNum  设置母线插接箱数量
 * @param index  母线编号
 * @param num    数量
 */
void BUS_SetShm::setBoxNum(int index, int num)
{
    shm->getBus(index)->devNum = num;
    QString str = QString::number(num,10);
    QString name = QString("bus_boxNum_%1").arg(index+1);
    sys_configFile_writeParam(name,str);
}
