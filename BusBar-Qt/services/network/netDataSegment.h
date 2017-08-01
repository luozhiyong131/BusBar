/*
 * datasegment.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef NETDATA_NETDATASEGMENT_H_
#define NETDATA_NETDATASEGMENT_H_

#include "netDataPacket.h"

#define DATA_DEV_VERSION		1 /*设备通讯类型*/


/**
 * 在网络中传输 数据库包
 */
typedef struct
{
    uchar addr;	/*地址*/
    uchar fn[2];	/*功能码*/
    ushort len; /*数据长度*/
    uchar *data; /*数据*/
}dev_data_packet;

int data_packet_sent(dev_data_packet *msg);
int data_packet_analytic(uchar *buf, ushort len, dev_data_packet *pkt);

#endif /* NETDATA_NETDATASEGMENT_H_ */
