#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>

#define LINE_NUM  3
#define LOOP_NUM  9
#define INPUT_NUM 10
#define OUTPUT_NUM 42
#define SENOR_NUM 3
#define NAME_SIZE 32
#define DEV_NUM 33
#define ARRAY_SIZE 255 //一包数据最长

// 倍率定义
#define COM_RATE_VOL	1.0    // 电压
#define COM_RATE_CUR	10.0    // 电流
#define COM_RATE_POW	1000.0  // 功率
#define COM_RATE_ELE	10.0    // 电能
#define COM_RATE_PF     100.0   // 功率因素
#define COM_RATE_TEM	1.0    // 温度
#define COM_RATE_HUM	1.0    // 湿度

/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
struct sDataUnit {
    ushort value; // 值
    ushort min; // 最小值
    ushort max; // 最大值
    ushort alarm; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    ushort crMin; // 最小值
    ushort crMax; // 最大值
    ushort crAlarm; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct sObjData
{
    int id;
    char name[NAME_SIZE];

    sDataUnit vol; // 电压
    sDataUnit cur; // 电流

    ushort pow; // 功率
    uint ele; // 电能

    uchar pf; // 功率因素
    uchar sw; // 开关状态 0 表示未启用

    uchar hz; // 电压频率
    ushort activePow; // 有功功率值

    uint ratedCur; // 额定电流
    uint wave; // 谐波值
    uint tem;
    uchar delay;
};

/**
 * 环境数据结构体
 */
struct sEnvData
{
    uchar envNum;
    sDataUnit tem[SENOR_NUM]; // 温度
    sDataUnit hum[SENOR_NUM]; // 湿度

    uchar door[SENOR_NUM]; // 门禁
    uchar water[SENOR_NUM]; // 水浸
    uchar smoke[SENOR_NUM]; // 烟雾
};

/**
 * 设备数据结构体：
 */
struct sDevData
{
    uchar lineNum;   //  数量
    sObjData line[LINE_NUM]; // 相数据

    uchar loopNum;
    sObjData loop[LOOP_NUM]; // 回路数据

    uchar inputNum;
    sObjData input[INPUT_NUM]; //输入数据

    uchar outputNum;
    sObjData output[OUTPUT_NUM]; //位数据

    sObjData tg; // 回路数据
    sEnvData env; // 环境数据
};

/**
 * RTU传输统计结构体
 */
struct sRtuCount
{
    uint count;
    uint okCount;
    uint errCount;

    uint longCount; // 连续丢命令
    uint longFlag;
};

/**
 * 数据包
 */
struct sDataPacket
{
    uchar id;  // 设备号
    uint devType; //设备类型
    uchar devSpec; // 设备规格 A\B\C\D
    uchar txType; // 通讯类型 0  1:SNMP  2：Zebra

    uchar alarm; // 工作状态 ==0 正常
    uchar offLine; //离线标志 > 0在线

    char ip[NAME_SIZE]; //设备IP
    char mac[NAME_SIZE]; // MAC地址
    char name[NAME_SIZE]; // 设备名称
    char versionStr[NAME_SIZE];

    sDevData data; //设备数据
    sRtuCount rtuCount; // 传输情况

    uchar dc; // 交直流标志位
    uchar hz; // 电压频率
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort version;
    ushort reserve;
};


struct sDevPackets{
    uchar devNum; // 高数数量
    sDataPacket   dev[DEV_NUM+1];
};

#endif // DATAPACKET_H
