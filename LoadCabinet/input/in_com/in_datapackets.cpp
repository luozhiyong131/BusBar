/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_datapackets.h"

IN_DataPackets::IN_DataPackets()
{    
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

IN_DataPackets *IN_DataPackets::bulid()
{
    static IN_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new IN_DataPackets();
    return sington;
}

sDataPacket *IN_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}

