#ifndef BUS_RTURECV_H
#define BUS_RTURECV_H
#include "bus_rtusent.h"
#include "bus_rtucmdenum.h"

struct BUS_RtuRecvLine {
    ushort vol; // 电压值
    ushort cur; // 电流值
    ushort pow; // 功率值
    ushort activePow; // 视在功率
    uint ele; // 电能值

    ushort minVol; // 最小电压
    ushort maxVol; // 最大电压
    ushort minCur; // 最小电流
    ushort maxCur; // 最大电流

    ushort wave; // 谐波值
    uchar pf; // 功率因素
    uchar sw; // 开关
};

struct BUS_RtuEnvUnit {
    uchar value;
    uchar min;
    uchar max;
};

struct BUS_RtuRecvEnv {
    BUS_RtuEnvUnit tem; // 温度
    BUS_RtuEnvUnit hum; // 湿度
};

struct BUS_RtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    uchar version; // 版本号

    BUS_RtuRecvLine data[BUS_RTU_LINE_NUM];
    BUS_RtuRecvEnv  env[BUS_RTU_TH_NUM];
    uchar lineNum; // 相数
    uchar rate; //频率
    uchar dc; // 交直流标志位

    uchar lps; // 防雷开关
    uchar pl[LINE_NUM]; // 负载百分比
    uchar hc; //谐波通道(00表示A路电压通道，01表示B路电压通道，02表示C路电压通道 03表示A路电流通道，04表示B路电流通道，05表示C路电流通道)
    ushort thd[BUS_RTU_THD_NUM+5]; // 庇波含量

    ushort crc; // 检验码
};

bool bus_rtu_recv_packet(uchar *buf, int len, BUS_RtuRecv *pkt);

#endif // BUS_RTURECV_H
