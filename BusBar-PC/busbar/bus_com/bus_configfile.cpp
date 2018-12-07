#include "bus_configfile.h"

BUS_ConfigFile::BUS_ConfigFile()
{
    mItem = new BUS_sConfigItem();
    for(int i=0; i<BUS_NUM; ++i) {
        mItem->serials[i] = nullptr;
    }
}

BUS_ConfigFile *BUS_ConfigFile::bulid()
{
    static BUS_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new BUS_ConfigFile();
    return sington;
}

void BUS_ConfigFile::init()
{
    for(int i=0; i<BUS_NUM; ++i) {
        mItem->devNums[i] = getDevNum(i);
        mItem->comNames[i] = getSerialName(i);
    }
}

void BUS_ConfigFile::save()
{
    for(int i=0; i<BUS_NUM; ++i) {
        setDevNum(mItem->devNums[i], i);
        setSerialName(mItem->comNames[i], i);
    }
}
