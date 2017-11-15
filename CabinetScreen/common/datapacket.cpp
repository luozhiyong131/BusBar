/*
 * datapacket.cpp
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "datapacket.h"

static sDataPacket *gDevDataPacket = nullptr;

sDataPacket *get_dev_dataPacket()
{
    if(gDevDataPacket == nullptr) {
        gDevDataPacket = new sDataPacket();
        memset(gDevDataPacket, 0, sizeof(sDataPacket));
    }
    return gDevDataPacket;
}
