#ifndef DATAPACKET_H
#define DATAPACKET_H
/*
 * datapacket.h
 * 数据包结构体定义思路
 * 	1、数据包中包含四条母线数据
 * 	2、一条母线包括最多20个插接箱数据
 * 	3、一个插接箱包括最多3个输出位
 * 	4、一个输出位包括基本的数据结体
 *
 *  Created on: 2017年5月24日
 *      Author: Lzy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 3 // 三相
#define OUTPUT_NUM 3 // 三个插接位
#define BOX_NUM 20 // 插接箱数量
#define BUS_NUM 4  // 四条母线
#define NAME_LEN	32 // 名称最大长度


/**
 * 统计数据结构体
 */
typedef struct _sTgObjData {
    int vol; // 电压
    int cur;  // 电流

    int pow; // 功率
    int ele; // 电能
    int pf; // 功率因素
}sTgObjData;


/**
 * 数据单元：包括当前值，阈值，临界值，报警状态等
 */
typedef struct _sDataUnit {
    int value[3]; // 值
    int min[3]; // 最小值
    int max[3]; // 最大值
    int alarm[3]; // 报警值
    int flag; // 标志 0表示未纪录 1表示已纪录

    int crMin[3]; // 临界最小值
    int crMax[3]; // 临界最大值
    int crAlarm[3]; // 临界报警值
    int crFlag[3];
}sDataUnit;

/**
 * 插接位数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
typedef struct _sOutputData {
    int lineNum; //相数
    sDataUnit vol; // 电压
    sDataUnit cur;  // 电流

    int pow[3]; // 功率
    int ele[3]; // 电能
    int pf[3]; // 功率因素

    sTgObjData tgOutput; // 插接位统计信息
    int ratedCur; // 额定电流
    char outputAlarm; // 插接位报警
    char outputStatus; // 插接位状态
    char outputName[NAME_LEN]; // 插接位名称
}sOutputData;

/**
 * 环境数据结构体
 */
typedef struct _sEnvData {
    sDataUnit tem; // 温度
    sDataUnit hum; // 湿度
}sEnvData;

/**
 * 插接箱数据结构体：包括最多三个插接位，插接箱名称
 */
typedef struct _sBoxData {
    char offLine; // 离线标识
    int outputNum; // 插接位数量

    int sw[OUTPUT_NUM]; // 开关状态
    sOutputData output[OUTPUT_NUM]; // 插接位3个
    sEnvData env; // 环境状态

    sTgObjData tgBox; // 插接箱统计信息
    char boxAlarm; // 插接箱报警
    char boxStatus; // 插接箱状态
    char boxName[NAME_LEN]; // 插接箱名称
    int rate; // 电压频率
}sBoxData;

/**
 * 母线数据结构体：包括插接箱数据，电压频率 母线名称
 */
typedef struct _sBusData{
    int boxNum; // 插接箱数量
    sBoxData   box[BOX_NUM];  // 最多20个插接箱

    sTgObjData tgBus; // 母线统计信息
    int rate; // 电压频率
    int ratedCur; // 额定电流
    char busAlarm; // 总线报警
    char busStatus; // 母线状态
    char busName[NAME_LEN]; // 母线名称
}sBusData;


typedef struct _sDataPacket
{
    sBusData data[BUS_NUM];  // 四条母线数据
}sDataPacket;


sDataPacket *share_mem_get();
void share_mem_init();
void share_mem_free();
void share_mem_del();

#endif // DATAPACKET_H