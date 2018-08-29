#ifndef IN_RTUPACKET_H
#define IN_RTUPACKET_H
#include "in_rtusent.h"

struct IN_sRtuLine {
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

struct IN_sRtuEnvUnit {
    uchar value;
    uchar min;
    uchar max;
};

struct IN_sRtuEnv {
    IN_sRtuEnvUnit tem; // 温度
    IN_sRtuEnvUnit hum; // 湿度
};

struct IN_sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    uchar version; // 版本号

    IN_sRtuLine data[IN_RTU_LINE_NUM];
    IN_sRtuEnv  env[IN_RTU_TH_NUM];
    uchar lineNum; // 相数
    uchar rate; //频率
    uchar dc; // 交直流标志位

    ushort crc; // 检验码
};

#endif // IN_RTUPACKET_H
