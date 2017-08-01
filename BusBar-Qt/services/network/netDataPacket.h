/*
 * netdata.h
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */

#ifndef NETDATA_NETDATAPACKET_H_
#define NETDATA_NETDATAPACKET_H_

#include "udpsent.h"

#define DATA_MSG_SIZE	512		/*数据缓冲区大小*/
#define DEV_CODE_SIZE	4		/*设备代号位数*/
#define DATA_MSG_CODE_SIZE	9

#define DATA_MSG_HDR	0x7E	/*信息头~*/
#define DATA_MSG_STX	0x5E	/*标识字^*/
#define DATA_MSG_ED	0x23	/*结束符*/

#define DATA_MSG_SERVICE	0x10	/*服务端标志*/
#define DATA_MSG_CLIENT		0x03	/*客户端标志*/

/*定义通讯类型*/
typedef enum {
	TRA_TYPR_UDP=1, /*UDP通讯*/
	TRA_TYPR_TCP,
	//===    请在这里增加所需要的通讯类型
}data_traffic_type;


/*错误码定义*/
typedef enum {
	DATA_ERR_ABNORMAL=-1, /*数据不完整错误*/
	DATA_ERR_HEAD=-2, /*同步头错误*/
	DATA_ERR_END=-3, /*结束符错误*/
	DATA_ERR_XOR=-4,/*校验码错误*/
}data_return_err;

/*代号段结构体*/
typedef struct
{
	uchar devCode[DEV_CODE_SIZE]; /*设备代号*/
	uchar type; /*通讯类型*/
	uchar version; /*版本号*/
	uchar trans;	/*服务端发送标志：10H 客户端应答标志：03H */
	ushort reserve; /*预留2字节*/
}data_code;

/**
 * 数据包结构体，
 */
typedef struct
{
	uchar hdr;	/*信息头 0x7E*/
	uchar stx;	/*标识字0x5E*/
	data_code code; /*代号段*/
	ushort len; /*数据长度 */
	uchar *data;	/*数据段*/
	ushort XOR; /*校验码*/
	uchar ED; /*结束符*/
}data_packet;

int data_msg_packetSent(data_code *code,uchar *buf, ushort len);
int data_msg_analytic(uchar *buf, ushort len, data_packet *msg);


#endif /* NETDATA_NETDATAPACKET_H_ */
