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

void SetShm::setVolAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=0; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<LINE_NUM; ++k) {
                setThresholdUnit( k, item, box->data.cur);
            }
        }
    }
}

void SetShm::setLoopCurAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<LINE_NUM; ++k) {
                setThresholdUnit( k, item, box->data.cur);
            }
        }
    }
}

void SetShm::setLineCurAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBoxData *bus = &(shm->data[i].box[0]);
        for(int k=0; k<LINE_NUM; ++k)
            setThresholdUnit(k, item, bus->data.cur);
    }
}

void SetShm::setLineTempAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBoxData *bus = &(shm->data[i].box[0]);
        for(int k=0; k<SENSOR_NUM; ++k)
            setThresholdUnit(k, item, bus->env.tem);
    }
}

void SetShm::setLoopTempAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *busData = &(shm->data[i]);
        for(int j=1; j<=busData->boxNum; ++j)
        {
            sBoxData *box = &(busData->box[j]);
            for(int k=0; k<SENSOR_NUM; ++k) {
                setThresholdUnit( k, item, box->env.tem);
            }
        }
    }
}

bool SetShm::saveItem(DbThresholdItem &item)
{
    bool ret = false;
    sDataUnit *unit=NULL;

    sBusData *bus = &(shm->data[item.bus]);
    sBoxData *box = &(bus->box[item.box]);
    switch(item.type) // 阈值类型 1 电压阈值  2 电流阈值 3 温度
    {
    case 1:
        unit = &(box->data.vol);
        break;

    case 2:
        unit = &(box->data.cur);
        break;

    case 3:
        unit = &(box->env.tem);
        break;
    }

    if(unit) {
        setThresholdUnit(item.num, item, (*unit));
    }

    return ret;
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
        boxNum = num / LINE_NUM + 1;
        num = num % LINE_NUM ;
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

/**
 * @brief SetShm::setLineRatedCur  设置母线额定电流
 * @param index  母线编号
 * @param data   额定电流值
 */
void SetShm::setLineRatedCur(int index, int data)
{
    sBusData *bus = &(shm->data[index]);
    bus->box[0].ratedCur = data;
    QString str = QString::number(bus->box[0].ratedCur,10);
    QString groupStr = QString("Line%1").arg(index+1);
    sys_configFile_writeParam("rateCur",str,groupStr);
}

/**
 * @brief SetShm::setLineBoxNum  设置母线插接箱数量
 * @param index  母线编号
 * @param num    数量
 */
void SetShm::setLineBoxNum(int index, int num)
{
    sBusData *bus = &(shm->data[index]);
    bus->boxNum = num ;
    QString str = QString::number(bus->boxNum,10);
    QString groupStr = QString("Line%1").arg(index+1);
    sys_configFile_writeParam("boxNum",str,groupStr); // Line1/boxNum
}
