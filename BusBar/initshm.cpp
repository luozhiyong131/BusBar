#include "initshm.h"
#include "dbthreshold.h"

InitShm::InitShm(QObject *parent) : QThread(parent)
{
    shm = get_share_mem(); // 获取共享内存
    start();
}

/**
 * @brief 初始化插接箱数量
 */
void InitShm::initBoxNum()
{
    for(int i=0; i<BUS_NUM; ++i) {
        shm->data[i].boxNum = 18; // 18个插接箱
    }
}


void InitShm::initThresholdUnit(int bus, int type, int num, sDataUnit &unit, int max)
{
    DbThresholdItem item;
    item.bus = bus;
    item.type = type;
    item.num = num;

    bool ret = DbThreshold::bulid()->getItem(item);
    if(ret) {
        unit.min[num] = item.min;
        unit.max[num] = item.max;
        unit.crMin[num] = item.crmin;
        unit.crMax[num] = item.crmax;
    } else {
         unit.max[num] = max;
         unit.crMax[num] = max;
    }
}

void InitShm::initBoxThreshold()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = &(shm->data[i]);
        for(int j=0; j<BOX_NUM; ++j)
        {
            sBoxData *box = &(bus->box[j]);
            for(int k=0; k<3; ++k)
            {
                int num = (j << 8) + k;
                initThresholdUnit(i, 3, num, box->data.cur, 630);
                initThresholdUnit(i, 5, num, box->env.tem, 99);
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
            initThresholdUnit(i, 2, k, bus->data.cur, 2600);
            initThresholdUnit(i, 4, k, bus->env.tem, 99);
        }
    }
}


void InitShm::initThreshold()
{
    initBusThreshold();
    initBoxThreshold();
}

void InitShm::run()
{
     initBoxNum();
    initThreshold();

}
