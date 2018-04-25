#ifndef DATAPACKET_H
#define DATAPACKET_H
/*
 * datapacket.h
 * 数据包结构体定义思路
 * 	1、数据包中包含四条母线数据
 * 	2、一条母线包括最多20个接插箱数据
 * 	LINE_NUM、一个接插箱包括最多3个输出位
 * 	4、一个输出位包括基本的数据结体
 *
 *  Created on: 2017年5月24日
 *      Author: Lzy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 9 // 三相
#define LINE_NUM_MAX 9 // 三相
#define BOX_NUM 32 // 接插箱数量
#define BUS_NUM 4  // 四条母线
#define NAME_LEN	32 // 名称最大长度
#define SENSOR_NUM 3 // 二个传感器

#define SRC_DATA_LEN_MAX 255 //一包数据最长 —— 用于对接动环

/**
 * 统计数据结构体
 */
typedef struct _sTgObjData {
    int vol; // 电压
    int cur;  // 电流

    int pow; // 功率
    int ele; // 电能
    int pf; // 功率因素
    int apPow; // 袖在功率
    int tem;
}sTgObjData;

typedef struct _sLineTgObjData {
    int vol[3]; // 电压
    int cur[3];  // 电流

    int pow[3]; // 功率
    int ele[3]; // 电能
    int pf[3]; // 功率因素
    int apPow[3]; // 袖在功率
    int tem[3];
}sLineTgObjData;

/**
 * 数据单元：包括当前值，阈值，临界值，报警状态等
 */
typedef struct _sDataUnit {
    int value[LINE_NUM_MAX]; // 值
    int min[LINE_NUM_MAX]; // 最小值
    int max[LINE_NUM_MAX]; // 最大值
    int alarm[LINE_NUM_MAX]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    int crMin[LINE_NUM_MAX]; // 临界最小值
    int crMax[LINE_NUM_MAX]; // 临界最大值
    int crAlarm[LINE_NUM_MAX]; // 临界报警值
}sDataUnit;

/**
 * 插接位数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
typedef struct _sObjData {
    int lineNum; //相数
    sDataUnit vol; // 电压
    sDataUnit cur;  // 电流

    int pow[LINE_NUM_MAX]; // 功率
    int ele[LINE_NUM_MAX]; // 电能
    int pf[LINE_NUM_MAX]; // 功率因素
    int sw[LINE_NUM_MAX]; // 开关状态
    int apPow[LINE_NUM_MAX]; // 视在功率
    int ratedCur[LINE_NUM_MAX]; // 额定电流
    int wave[LINE_NUM_MAX]; // 谐波值
}sObjData;


/**
 * 环境数据结构体
 */
typedef struct _sEnvData {
    sDataUnit tem; // 温度
    sDataUnit hum; // 湿度
}sEnvData;

/**
 * 接插箱数据结构体：包括最多三个插接位，接插箱名称
 */
typedef struct _sBoxData {
    char offLine; // 离线标识
    int loopNum; // 回路数量
    char version;

    sObjData data; // 回路数据
    char loopName[LINE_NUM_MAX][NAME_LEN]; // 回路名称
    sEnvData env; // 环境状态

    sTgObjData tgBox; // 接插箱统计信息
    sLineTgObjData lineTgBox;
    char boxAlarm, boxVolAlarm, boxCurAlarm, boxEnvAlarm; // 接插箱报警
    char boxStatus; // 接插箱状态
    char boxSpec; //  0 表示 SI  1 表示 IP
    char boxName[NAME_LEN]; // 接插箱名称

    int ratedCur; // 额定电流
    int rate; // 电压频率
    char dc; // 交直流标志位
}sBoxData;

/**
 * 母线数据结构体：包括接插箱数据，电压频率 母线名称
 */
typedef struct _sBusData{
    int boxNum; // 接插箱数量
    sBoxData   box[BOX_NUM];  // 最多20个接插箱
    char busName[NAME_LEN]; // 母线名称
}sBusData;

/**
 * 转发动环数据： 所有接插相原始数据
 */
typedef struct _sSrcData{
    u_char len[BOX_NUM];
    u_char array[BOX_NUM][SRC_DATA_LEN_MAX];
}sSrcData;


typedef struct _sDataPacket
{
    sBusData data[BUS_NUM];  // 四条母线数据
    sSrcData srcData[BUS_NUM];  //放一起[申请到共享内存]
}sDataPacket;

/**
 * 设置地址枚举：包括各种参数的地址
 */
enum  sSetType{
     SetAddress        = 0x1001           //地址
    ,VoltageMAX_L1     = 0x1002           //电压上限
    ,VoltageMIN_L1     = 0x1003           //电压下限
    ,VoltageMAX_L2     = 0x1004
    ,VoltageMIN_L2     = 0x1005
    ,VoltageMAX_L3     = 0x1006
    ,VoltageMIN_L3     = 0x1007
    ,VoltageMAX_L4     = 0x1008
    ,VoltageMIN_L4     = 0x1009
    ,VoltageMAX_L5     = 0x100A
    ,VoltageMIN_L5     = 0x100B
    ,VoltageMAX_L6     = 0x100C
    ,VoltageMIN_L6     = 0x100D
    ,VoltageMAX_L7     = 0x100E
    ,VoltageMIN_L7     = 0x100F
    ,VoltageMAX_L8     = 0x1010
    ,VoltageMIN_L8     = 0x1011
    ,VoltageMAX_L9     = 0x1012
    ,VoltageMIN_L9     = 0x1013
    ,CurrentMAX_L1     = 0x1020           //电流上限
    ,CurrentMIN_L1     = 0x1021           //电流下限
    ,CurrentMAX_L2     = 0x1022
    ,CurrentMIN_L2     = 0x1023
    ,CurrentMAX_L3     = 0x1024
    ,CurrentMIN_L3     = 0x1025
    ,CurrentMAX_L4     = 0x1026
    ,CurrentMIN_L4     = 0x1027
    ,CurrentMAX_L5     = 0x1028
    ,CurrentMIN_L5     = 0x1029
    ,CurrentMAX_L6     = 0x102A
    ,CurrentMIN_L6     = 0x102B
    ,CurrentMAX_L7     = 0x102C
    ,CurrentMIN_L7     = 0x102D
    ,CurrentMAX_L8     = 0x102E
    ,CurrentMIN_L8     = 0x102F
    ,CurrentMAX_L9     = 0x1030
    ,CurrentMIN_L9     = 0x1031
    ,temperatureMAX_1  = 0x1032           //温度上限
    ,temperatureMIN_1  = 0x1033           //温度下限
    ,temperatureMAX_2  = 0x1034
    ,temperatureMIN_2  = 0x1035
    ,temperatureMAX_3  = 0x1036
    ,temperatureMIN_3  = 0x1037 
    ,temperatureMAX_4  = 0x1038
    ,temperatureMIN_4  = 0x1039
    ,temperatureMAX_5  = 0x103A
    ,temperatureMIN_5  = 0x103B
    ,temperatureMAX_6  = 0x103C
    ,temperatureMIN_6  = 0x103D
    ,temperatureMAX_7  = 0x103E
    ,temperatureMIN_7  = 0x103F
    ,temperatureMAX_8  = 0x1041
    ,temperatureMIN_8  = 0x1042
    ,temperatureMAX_9  = 0x1043
    ,temperatureMIN_9  = 0x1044
    ,BaudRate          = 0x1045           //波特率
};

sDataPacket *share_mem_get();
void share_mem_init();
void share_mem_free();
void share_mem_del();

#endif // DATAPACKET_H
