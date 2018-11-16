/*
 * pduhashdatasave.cpp
 * PDU设备数据保存入口文件
 *  入口函数：void pdu_hashData_save(pdu_devData_packet *packet)
 *    入口函数被NetDataAnalyze类调用，来保存设备数据
 *
 *  功能处理函数：void pdu_hashData_function(PduDataPacket *dev,pdu_dev_data *data)
 *      此函数，会根据功能码调用相应的子模块接口函数进入数据处理
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "pduhashdatasave.h"
#include "pduhashdevdatasave.h"
//#include "pduhashoutputsave.h"
//#include "pduhashdevinfosave.h"
//#include "pduhashdevusrsave.h"
//#include "pduhashdevnetsave.h"
//#include "pduhashmanslave.h"
//#include "pduhashdevchartsave.h"




/**
 * @brief pdu_hashData_function
 * @param dev
 * @param data
 */
static void pdu_hashData_function(sBoxData *dev,pdu_dev_data *data)
{
    int fc = data->fn[0]; //根据功能码，进行分支处理

    switch (fc)
    {
    case PDU_CMD_STATUS: //设备工作状态
        dev->dc = data->fn[1];
        dev->boxStatus = data->data[0]; //0正常 >0不正常
        dev->boxSpec = 1;
        break;

    case PDU_CMD_RATE:
        dev->rate = data->data[0];
        break;

    case PDU_CMD_LINE: // 设备相参数
    case PDU_CMD_OUTPUT: // 设备输出位
    case PDU_CMD_ENV: //环境数据
        pdu_hashDevData_save(dev, data);
        break;

    case PDU_CMD_DEVINFO: // 设备信息
        sprintf(dev->boxName, "%s",data->data);
        break;

        //    case PDU_CMD_OUTPUT_NAME: // 输出位名称
        //        pdu_output_name(dev->output->name, data);
        //        break;

    default:
        //        qDebug() << "pdu_hashData_function err" << fc;
        break;
    }
}



/**
 * @brief Hash数据保存的入口函数
 *  主要是针对代号段的处理，pdu_dev_code
 *      对数据进行网络传输类型、传输方向、及版本的验证;
 *      根据IP、代号段中的设备类型、设备号来查找对应的设备数据节点
 * @param packet
 */
void pdu_hashData_save(pdu_devData_packet *packet)
{
    static sDataPacket *dataPacket = share_mem_get();
    static sBoxData  *boxDev = NULL;

    bool ret = pdu_netData_check(packet->code->type, packet->code->trans);   /*网络传输类型、传输方向验证*/
    if(ret)
    {
        int devType = get_pdu_devCode(packet->code->devCode); // 获取设备类型码
        if(devType > 0)
        {
            int num = getByIp(packet->ip);
            int addr = packet->data->addr;
            boxDev  = &(dataPacket->data[num].box[addr]);

            if(packet->code->version == NET_DATA_VERSION) //版本号的验证
            {
                //    dev->devType = devType; //设备型号
                //   dev->devNum = packet->data->addr; // 设备地址
                //   dev->ip->set(packet->ip); //设备IP
                boxDev->offLine = OFF_LINE_TIME; //设备在线标识
                pdu_hashData_function(boxDev, packet->data); //功能预处理
            }
            else
                qDebug() << "NET DATA VERSION err";
        }
        else
            qDebug() << "get pdu dev Code err";
    }
    else
        qDebug() << "pdu netData check err";
}

