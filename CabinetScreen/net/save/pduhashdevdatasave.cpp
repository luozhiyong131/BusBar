/*
 * pduhashdevdatasave.cpp
 * PDU设备数据保存
 *  主要保存、电流、电压、功率、电能、及环境数据的保存
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "pduhashdevdatasave.h"

static sDevData *gDev=NULL;

/**
 * @brief 数据单元处理 主要针对 当前值、最大、小值等数据的处理
 * @param unit
 * @param data
 */
static void pdu_hash_unitData(sDataUnit *unit, pdu_dev_data *data)
{
    int *ptr = NULL;
    int sizeBit = 2;

    int fc = data->fn[1] & 0x0f; // 处理功能码，第二字节的低四位数据
    switch (fc)
    {
    case PDU_CMD_VALUE:
        ptr = unit->value;
        break;

    case PDU_CMD_MIN:
        ptr = unit->min;
        break;

    case PDU_CMD_MAX:
        ptr = unit->max;
        break;

    case PDU_CMD_ALARM:
        sizeBit = 1;
        ptr = unit->alarm;
        return; // break;

    case PDU_CDM_CRMIN:
        ptr = unit->crMin;
        break;

    case PDU_CMD_CRMAX:
        ptr = unit->crMax;
        break;

    case PDU_CMD_CRALARM:
        sizeBit = 1;
        ptr = unit->crAlarm;
        break;

    default:
        qDebug() << "pdu_hashUnitData err" << fc;
        break;
    }

    if(ptr)
        pdu_saveHash_intData(ptr, data->len, data->data, sizeBit);
}


/**
 * @brief 设备对象数据的处理 主要电流、电压、功率、电能
 * @param obj
 * @param data
 */
static void pdu_hash_objData(sObjData *obj,pdu_dev_data *data)
{
    int *ptr = NULL;
    int sizeBit = 2;

    int fc = data->fn[1] >> 4; // // 处理功能码，第二字节的高四位
    switch (fc)
    {
    case PDU_CMD_NUM_SIZE: // 回路数量
        gDev->lineNum = data->data[0];
        return;

    case PDU_CMD_CUR: // 电流
        pdu_hash_unitData(&(obj->cur), data);
        break;

    case PDU_CMD_VOL: // 电压
        pdu_hash_unitData(&(obj->vol), data);
        break;

    case PDU_CMD_POW: // 功率
        sizeBit = 4;
        ptr = obj->pow;
        break;

    case PDU_CMD_ELE: // 电能
        sizeBit = 4;
        ptr = obj->ele;
        break;

    case PDU_CMD_PF: // 功率因素
        ptr = obj->pf;
        break;

    case PDU_CMD_SW: // 开关状态
        sizeBit = 1;
        ptr = obj->sw;
        break;

//    case PDU_CMD_CA: // 排碳量
//        ptr = obj->carbon;
//        break;

//    case PDU_CMD_RATE: //电压频率
//        ptr = obj->rate;
//        break;

    default:
        qDebug() << "pdu_hash_objData err" << fc;
        break;
    }

    if(ptr)
        pdu_saveHash_intData(ptr, data->len, data->data, sizeBit);
}


/**
 * @brief 环境数据的处理
 * @param env
 * @param data
 */
static void pdu_hash_envData(sEnvData *env,pdu_dev_data *data)
{
    int *ptr = NULL;
    int sizeBit = 1;

    int fc = data->fn[1] >> 4; // // 处理功能码，第二字节的高四位
    switch (fc)
    {
    case PDU_CMD_TEMP: // 温度
        pdu_hash_unitData(&(env->tem), data);
        break;

    case PDU_CMD_HUM: //湿度
        pdu_hash_unitData(&(env->hum), data);
        break;

//    case PDU_CMD_DOOR: //门禁
//        ptr = env->door;
//        break;

//     case PDU_CMD_WATER: //水浸
//        ptr = env->water;
//        break;

//     case PDU_CMD_SMOKE: //烟雾
//        ptr = env->smoke;
//        break;

     default:
        qDebug() << "pdu_hash_envData err" << fc;
        break;
    }
    if(ptr)
        pdu_saveHash_intData(ptr, data->len, data->data, sizeBit);
}


/**
 * @brief 保存设备数据 主要针对PduDevData类操作
 * @param dev
 * @param data
 */
void pdu_hashDevData_save(sDevData *dev, pdu_dev_data *data)
{
    gDev = dev;
    int fn = data->fn[0]; // 处理功能码第一位数据
    switch (fn)
    {
    case PDU_CMD_LINE: //相电气参数
        pdu_hash_objData(&(dev->data), data);
        break;

    case PDU_CMD_OUTPUT: // 输出位电气参数
//        pdu_hash_objData(dev->output, data);
        break;

    case PDU_CMD_ENV: //环境数据
        pdu_hash_envData(&(dev->env), data);
        break;

    default:
//        qDebug() << "pdu_hashDevData_save err" << fn;
        break;
    }
}



