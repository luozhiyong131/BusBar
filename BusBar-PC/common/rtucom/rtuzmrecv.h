#ifndef RTUZMRECV_H
#define RTUZMRECV_H
#include "rtuzmreg.h"

#define ZM_UNIT_NUM 43

struct ZM_sDataUnit {
    ushort value[ZM_UNIT_NUM]; // 值
    ushort min[ZM_UNIT_NUM]; // 最小值
    ushort max[ZM_UNIT_NUM]; // 最大值
    ushort alarm[ZM_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    ushort crMin[ZM_UNIT_NUM]; // 最小值
    ushort crMax[ZM_UNIT_NUM]; // 最大值
    ushort crAlarm[ZM_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct ZM_sObjData
{
    ushort id, num;
    char name[NAME_SIZE];

    ZM_sDataUnit vol; // 电压
    ZM_sDataUnit cur; // 电流

    ushort pow[ZM_UNIT_NUM]; // 功率
    ushort ele[ZM_UNIT_NUM]; // 电能

    ushort pf[ZM_UNIT_NUM]; // 功率因素
    ushort sw[ZM_UNIT_NUM]; // 开关状态 0 表示未启用

    ushort activePow[ZM_UNIT_NUM]; // 有功功率值
    ushort delay[ZM_UNIT_NUM];
};

struct ZM_sEnv
{
    ZM_sDataUnit tem; // 温度
    ZM_sDataUnit hum; // 湿度

    ushort door[3]; // 门禁
    ushort water[3]; // 水浸
    ushort smoke[3]; // 烟雾
};

struct ZM_sRtuPacket {
    ZM_sObjData line; // 相数据
    ZM_sObjData loop; // 回响数据
    ZM_sObjData output; //位数据
    ZM_sEnv env;

    ushort hz[3]; // 频率
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort id, devSpec;
    ushort version;
    char ip[24], mac[40];
    ushort reserve;
};


struct ZM_sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;
    ZM_sRtuPacket data;
    ushort crc; // 检验码
};


class RtuZmRecv
{
public:
    RtuZmRecv();
    virtual bool recvPacket(uchar *buf, int len, ushort reg, ZM_sRtuRecv *pkt);

protected:
    virtual void devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt);
    void devIpAddr(uchar *buf, int len, ZM_sRtuPacket &pkt);
    void devMac(uchar *buf, int len, ZM_sRtuPacket &pkt);

    bool rtuRecvPacket(uchar *buf, int len, ushort reg, ZM_sRtuPacket &pkt);
    bool rtuRecvCrc(uchar *buf, int len, ZM_sRtuRecv *msg);
    int rtuRecvHead(uchar *ptr,  ZM_sRtuRecv *pkt);

    uchar *rtuRecvData(uchar *ptr, int num, uint *value);
    uchar *rtuRecvData(uchar *ptr, int num, ushort *value);
    uchar *rtuRecvData(uchar *ptr, int num, uchar *value);
};

ushort *zm_reg_array(int id);

#endif // RTUMRECV_H
