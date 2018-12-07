#include "bus_datapackets.h"

BUS_DataPackets::BUS_DataPackets()
{
    memset(&mBus, 0, sizeof(sDevPackets)*BUS_NUM);
    initData();
}

BUS_DataPackets *BUS_DataPackets::bulid()
{
    static BUS_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new BUS_DataPackets();
    return sington;
}

void BUS_DataPackets::initBox()
{
    for(int i=0; i<BUS_NUM; ++i) {
        for(int j=1; j<=DEV_NUM; ++j) {

            sDataPacket *box = &(mBus[i].dev[j]);
            box->id = j;
            sprintf(box->name, "iBox-%d", j);

            for(int k=0; k<LOOP_NUM; ++k) {
                sprintf(box->data.loop[k].name, "loop-%d", k+1);
            }
        }
    }
}

void BUS_DataPackets::initBus()
{
     mBus[0].devNum = 10;
    for(int i=0; i<BUS_NUM; ++i) {
        sDataPacket *box = &(mBus[i].dev[0]);

        box->id = 0;
        sprintf(box->name, "0%d BUS", i+1);
    }
}

void BUS_DataPackets::initData()
{
    initBus();
    initBox();
}

