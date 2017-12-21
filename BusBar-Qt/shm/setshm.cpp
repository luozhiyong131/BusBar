#include "setshm.h"

SetShm::SetShm(QObject *parent) : QObject(parent)
{
    shm = get_share_mem(); // 获取共享内存
    //    mSetting = new QSettings("line.ini",QSettings::IniFormat);
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
            for(int k=0; k<LINE_NUM; ++k) {
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
        sBoxData *bus = &(shm->data[i].box[0]);
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
        sBoxData *bus = &(shm->data[i].box[0]);
        for(int k=0; k<3; ++k)
        {
            setThresholdUnit(k, item, bus->data.cur);
        }
    }
    DbThreshold::bulid()->setLineCurAll(item);
}



void SetShm::setLineTempAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
         sBoxData *bus = &(shm->data[i].box[0]);
        for(int k=0; k<3; ++k)
        {
            setThresholdUnit(k, item, bus->env.tem);
        }
    }

    DbThreshold::bulid()->setLineTempAll(item);
}


void SetShm::setTempAll(DbThresholdItem &item)
{
    for(int i=0; i<BUS_NUM; ++i)
    {
         sBoxData *bus = &(shm->data[i].box[0]);
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
            for(int k=0; k<LINE_NUM; ++k) {
                setThresholdUnit( k, item, box->env.tem);
            }
        }
    }
    DbThreshold::bulid()->setTempAll(item);
}

bool SetShm::saveItem(DbThresholdItem &item)
{
    bool ret = false;
    sDataUnit *unit=NULL;
    int boxNum=0, num = item.num;

    qDebug() <<"bus" <<item.bus << "Type" << item.type << "num" << item.num;

    sBusData *box = &(shm->data[item.bus]);
    sBoxData *bus = &(box->box[0]);
    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度
    {
    case 1:
        unit = &(bus->data.vol);
        break;

    case 2:
        unit = &(bus->data.cur);
        break;

    case 3:
        boxNum = num / LINE_NUM + 1;
        num = num % LINE_NUM ;
        unit = &(box->box[boxNum].data.cur);
        break;

    case 4:
        unit = &(bus->env.tem);
        break;

    case 5:
        boxNum = num / SENSOR_NUM + 1;
        num = num % SENSOR_NUM ;
        unit = &(box->box[boxNum].env.tem);
        break;
    }

    if(unit) {
        setThresholdUnit(num, item, (*unit));
        ret = DbThreshold::bulid()->saveItem(item);
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
        num = (num-1) % LINE_NUM ;
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
