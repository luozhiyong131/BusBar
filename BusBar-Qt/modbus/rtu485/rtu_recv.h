#ifndef RTU_RECV_H
#define RTU_RECV_H

#include "rtu_sent.h"

#define RTU_LINE_NUM 3 // 3相
#define RTU_TH_NUM 3 // 3个传感器

struct RtuRecvLine {
    ushort vol; // 电压值
    ushort cur; // 电流值
    ushort pow; // 功率值
    ushort apPow; // 视在功率
    uint ele; // 电能值
    ushort curAlarm; // 上限电流报警值
    ushort wave; // 谐波值
    uchar pf; // 功率因素
    uchar sw; // 开关
};

struct RtuRecvEnv {
    uchar tem; // 温度
    uchar hum; // 湿度
};

struct Rtu_recv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数

    RtuRecvLine data[RTU_LINE_NUM];
    RtuRecvEnv  env[RTU_TH_NUM];
    uchar lineNum;

    ushort crc; // 检验码
};

bool rtu_recv_packet(uchar *buf, int len, Rtu_recv *pkt);

#endif // RTU_RECV_H
