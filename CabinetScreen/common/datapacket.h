#ifndef DATAPACKET_H
#define DATAPACKET_H
/*
 * datapacket.h
 * 数据包结构体定义思路
 *
 *  Created on: 2017年5月24日
 *      Author: Lzy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 3 // 三相
#define DEV_NUM 2 // 设备数量
#define NAME_LEN	32 // 名称最大长度
#define SENSOR_NUM 3 // 二个传感器

#define IP_ADDR     "192.168.1.163"

/**
 * 统计数据结构体
 */
struct sTgObjData {
    int vol; // 电压
    int cur;  // 电流

    int pow; // 功率
    int ele; // 电能
    int pf; // 功率因素
};

/**
 * 数据单元：包括当前值，阈值，临界值，报警状态等
 */
struct sDataUnit {
    int value[LINE_NUM]; // 值
    int min[LINE_NUM]; // 最小值
    int max[LINE_NUM]; // 最大值
    int alarm[LINE_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    int crMin[LINE_NUM]; // 临界最小值
    int crMax[LINE_NUM]; // 临界最大值
    int crAlarm[LINE_NUM]; // 临界报警值
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
 struct sObjData {
    int lineNum; //相数
    sDataUnit vol; // 电压
    sDataUnit cur;  // 电流

    int pow[LINE_NUM]; // 功率
    int ele[LINE_NUM]; // 电能
    int pf[LINE_NUM]; // 功率因素
    int sw[LINE_NUM]; // 开关状态
    int apPow[LINE_NUM]; // 视在功率
};


/**
 * 环境数据结构体
 */
typedef struct _sEnvData {
    sDataUnit tem; // 温度
    sDataUnit hum; // 湿度
}sEnvData;

/**
 * 设备数据结构体：包括最多三个插接位，插接箱名称
 */
struct sDevData {
    int offLine; // 离线标识
    int devType;  //设备型号
    int devNum;  // 级联地址

    char addr; // 物理地址
    char ip[NAME_LEN];

    sObjData data; // 数据
    sEnvData env; // 环境状态
    sTgObjData tg; // 统计信息

    char status; // 设备状态
    char alarm, volAlarm, curAlarm, temAlarm, humAlarm; // 插接箱报警
    char devSpec;
    char name[NAME_LEN]; // 设备名称

    int lineNum; // 回路数量
    int ratedCur; // 额定电流
    int rate; // 电压频率
};


struct sDataPacket
{
    sDevData dev[DEV_NUM];  // 四条母线数据
    sTgObjData tg; // 统计信息
};

sDataPacket *get_dev_dataPacket();

#endif // DATAPACKET_H
