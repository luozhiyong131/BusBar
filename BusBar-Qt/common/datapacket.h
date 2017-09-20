#ifndef DATAPACKET_H
#define DATAPACKET_H
/*
 * datapacket.h
 * 数据包结构体定义思路
 * 	1、数据包中包含四条母线数据
 * 	2、一条母线包括最多20个插接箱数据
 * 	LINE_NUM、一个插接箱包括最多3个输出位
 * 	4、一个输出位包括基本的数据结体
 *
 *  Created on: 2017年5月24日
 *      Author: Lzy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 3 // 三相
#define BOX_NUM 32 // 插接箱数量
#define BUS_NUM 2  // 四条母线
#define NAME_LEN	32 // 名称最大长度
#define SENSOR_NUM 3 // 二个传感器

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


/**
 * 数据单元：包括当前值，阈值，临界值，报警状态等
 */
typedef struct _sDataUnit {
    int value[LINE_NUM]; // 值
    int min[LINE_NUM]; // 最小值
    int max[LINE_NUM]; // 最大值
    int alarm[LINE_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    int crMin[LINE_NUM]; // 临界最小值
    int crMax[LINE_NUM]; // 临界最大值
    int crAlarm[LINE_NUM]; // 临界报警值
}sDataUnit;

/**
 * 插接位数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
typedef struct _sObjData {
    int lineNum; //相数
    sDataUnit vol; // 电压
    sDataUnit cur;  // 电流

    int pow[LINE_NUM]; // 功率
    int ele[LINE_NUM]; // 电能
    int pf[LINE_NUM]; // 功率因素
    int sw[LINE_NUM]; // 开关状态
    int apPow[LINE_NUM]; // 视在功率
    int ratedCur[LINE_NUM]; // 额定电流
    int wave[LINE_NUM]; // 谐波值
}sObjData;


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
    int loopNum; // 回路数量

    sObjData data; // 回路数据
    char loopName[LINE_NUM][NAME_LEN]; // 回路名称
    sEnvData env; // 环境状态

    sTgObjData tgBox; // 插接箱统计信息
    char boxAlarm, boxCurAlarm, boxEnvAlarm; // 插接箱报警
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
    sObjData data; // 母线数据
    sEnvData env; // 环境状态
    sTgObjData tgBus; // 母线统计信息
    int rate; // 电压频率
    int ratedCur; // 额定电流

    char busCurAlarm; // 总线电流报警
    char busVolAlarm; // 总线电压报警
    char busEnvAlarm;
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
