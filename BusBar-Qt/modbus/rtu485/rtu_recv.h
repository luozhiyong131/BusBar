#ifndef RTU_RECV_H
#define RTU_RECV_H

#include "rtu_sent.h"

struct RtuRecvLine {
    ushort vol; // 电压值
    ushort cur; // 电流值
    ushort pow; // 功率值
    ushort apPow; // 视在功率
    uint ele; // 电能值

    ushort minVol; // 最小电压
    ushort maxVol; // 最大电压
    ushort minCur; // 最小电流
    ushort maxCur; // 最大电流

    ushort wave; // 谐波值
    uchar pf; // 功率因素
    uchar sw; // 开关
};

struct RtuEnvUnit {
    uchar value;
    uchar min;
    uchar max;
};

struct RtuRecvEnv {
    RtuEnvUnit tem; // 温度
    RtuEnvUnit hum; // 湿度
};

struct Rtu_recv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    uchar version;

    RtuRecvLine data[RTU_LINE_NUM];
    RtuRecvEnv  env[RTU_TH_NUM];
    uchar lineNum;
    uchar rate;
    uchar dc; // 交直流标志位

    ushort crc; // 检验码
};

bool rtu_recv_packet(uchar *buf, int len, Rtu_recv *pkt);

#endif // RTU_RECV_H
