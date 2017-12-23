/*
 * devDataSent.c
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "devDataSent.h"
#include "apptcpserver.h"
#include <QDebug>
#include "common/datapacket.h"
#include "common/common.h"

extern char currentBus;
static uchar gSentBuf[DATA_MSG_SIZE]={0};

#define LEN_DATA 5
static ushort valueBuf[LEN_DATA][LINE_NUM] = {100};
static ushort maxBuf[LEN_DATA][LINE_NUM] = {2*200};
static ushort minBuf[LEN_DATA][LINE_NUM] = {2*200};
static uchar  alarmBuf[LEN_DATA][LINE_NUM] = {1};
static ushort crMinBuf[LEN_DATA][LINE_NUM] = {300};
static ushort crMaxBuf[LEN_DATA][LINE_NUM] = {600};

static int data_msg_packetSent(uchar *buf, ushort len)
{
    android_sent(buf,len);
    //    len = udp_clientSentData(gSentBuf,len);


    return len;
}

static int dev_code_data(void)
{
    return 0x02010101;
}

static int data_packet_sent(dev_data_packet *msg)
{
    uchar *buf = gSentBuf;
    int type =TRA_TYPR_TCP;
    int num = dev_code_data();

    memset(buf,0,DATA_MSG_SIZE);
    ushort rtn = net_data_packets(num, type,msg, buf);
    rtn = data_msg_packetSent(buf, rtn);

    return rtn;
}

/**
 * 发送工作状态
 */
void sent_devStatus(dev_data_packet *msg, uchar status)
{
    msg->len = 1;
    msg->data = &status;

    msg->fn[0] = 0;
    msg->fn[1] = 0;
    data_packet_sent(msg);
}


/**
 * 发送数据包
 *  发送数据的条件：数据长度大于0 缓冲区地址有效
 */
static void sent_packet(dev_data_packet *msg)
{
    if(msg->len > 0) // 必需有数据
    {
        if(msg->data) // 数据指针有效
            data_packet_sent(msg);
    }
}

/**
 * 功  能：短整形变成字符串型数据
 * 入口参数：from-> 数据来源，len-> 数据长度
 * 出口参数：to->数据缓冲区
 * 返  回：数据长度
 */
static int shortToChar(ushort *form, int len, uchar *to)
{
    int i, offset=0;
    if(form)
    {
        memset(to,0, DATA_MSG_SIZE);
        for(i=0; i<len; ++i)
        {
            to[offset++] = form[i] >> 8; // 高位
            to[offset++] = form[i] & 0xFF; // 低8位
        }
    }

    return offset;
}

/**
 * 功  能：整形变成字符串型数据
 * 入口参数：from-> 数据来源，len-> 数据长度
 * 出口参数：to->数据缓冲区
 * 返  回：数据长度
 */
static int intToChar(uint *form, int len, uchar *to)
{
    int i, offset=0;

    if(form)
    {
        memset(to,0, DATA_MSG_SIZE);
        for(i=0; i<len; ++i)
        {
            to[offset++] = form[i] >> 24; // 高位
            to[offset++] = (form[i] >> 16) & 0xFF;
            to[offset++] = (form[i] >> 8) & 0xFF;
            to[offset++] = form[i] & 0xFF; // 低8位
        }
    }

    return offset;
}

/**
 * 功  能：发送数据单元数据
 * 参  数：unit->数据单元结构体
 * 		  buf->发送数据缓冲区
 * 		  len-> 数据长度
 */
static void sent_unit(_devDataUnit *unit, int len, uchar *buf, dev_data_packet *msg)
{
    int fn=1, fc = msg->fn[1];

    /* 发送当前值 */
    msg->fn[1] = fc + fn++;
    msg->data = buf;
    msg->len = shortToChar(unit->value,len,buf);
    sent_packet(msg);

    /*发送最小值*/
    msg->fn[1] = fc + fn++;
    msg->len = shortToChar(unit->min,len,buf);
    sent_packet(msg);

    /*发送最大值*/
    msg->fn[1] = fc + fn++;
    msg->len = shortToChar(unit->max,len,buf);
    sent_packet(msg);

    /*发送报警*/
    msg->fn[1] = fc + fn++;
    msg->len = len;
    msg->data = unit->alarm;
    sent_packet(msg);

    /*发送临界最小值*/
    msg->fn[1] = fc + fn++;
    msg->data = buf;
    msg->len = shortToChar(unit->crMin,len,buf);
    sent_packet(msg);

    /*发送临界最大值*/
    msg->fn[1] = fc + fn++;
    msg->data = buf;
    msg->len = shortToChar(unit->crMax,len,buf);
    sent_packet(msg);

    /*发送临界报警*/
    msg->fn[1] = fc + fn++;
    msg->len = len;
    msg->data = unit->crAlarm;
    sent_packet(msg);
}

/**
 * 功 能：发送数据对象 包括电流、电压、功率、电能、功率因素等
 */
static void sent_object(_devDataObj *obj, uchar *buf, dev_data_packet *msg)
{
    int fn=0, len = obj->len;

    /*电流*/
    fn += 1;
    msg->fn[1] = fn << 4;
    sent_unit(&(obj->cur), len, buf, msg);

    /*电压*/
    fn += 1;
    msg->fn[1] = fn << 4;
    sent_unit(&(obj->vol), len, buf, msg);

    /*功率*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = intToChar(obj->pow,len,buf); // 功率
    sent_packet(msg);

    /*电能*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = intToChar(obj->ele,len,buf); // 电能
    sent_packet(msg);

    /*功率因素*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = shortToChar(obj->pf,len,buf);
    sent_packet(msg);

    /*开关控制*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = obj->sw;
    msg->len = len;
    sent_packet(msg);

    /*排C量*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = shortToChar(obj->carbon,len,buf);
    sent_packet(msg);

    /*电压频率*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = shortToChar(obj->rate,len,buf); // 功率
    sent_packet(msg);

    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = shortToChar(obj->apPow,len,buf);
    sent_packet(msg);

    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = buf;
    msg->len = shortToChar(obj->wave,len,buf);
    sent_packet(msg);
}

/**
 * 功  能：发送温度、湿度、门禁、水浸等相关数据
 */
static void sent_envObject(_envDataObjct *obj, uchar *buf, dev_data_packet *msg)
{
    int fn=0, len = obj->len;

    /*湿度*/
    fn += 1;
    msg->fn[1] = fn << 4;
    sent_unit(&(obj->tem), len, buf, msg);

    /*湿度*/
    fn += 1;
    msg->fn[1] = fn << 4;
    sent_unit(&(obj->hum), len, buf, msg);

    /*门禁*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = obj->door;
    msg->len = 2;
    sent_packet(msg);

    /*水禁*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = obj->water;
    msg->len = 1;
    sent_packet(msg);

    /*烟雾*/
    fn += 1;
    msg->fn[1] = fn << 4;
    msg->data = obj->smoke;
    msg->len = 1;
    sent_packet(msg);
}

/**
 * 功  能：设备数据发送
 */
void sent_devData(uchar id, pduDevData *devData)
{
    static dev_data_packet msg;
    static uchar buf[DATA_MSG_SIZE] = {0};
    int fn=1;

    msg.num = 0;
    msg.addr = id;
    msg.fn[0] = fn++;
    sent_object(&(devData->line),buf, &msg);

    msg.fn[0] = fn++;
//    sent_object(&(devData->output),buf,&msg);

    msg.fn[0] = fn++;
//    sent_object(&(devData->output),buf,&msg);

    msg.fn[0] = fn++;
    sent_envObject(&(devData->env), buf,&msg);

    sent_devStatus(&msg, 1);
}

/**
 * 初始化数据  测试用，
 */
void init_unit(_devDataUnit *unit)
{
    unit->value = valueBuf[0];
    unit->max = maxBuf[0];
    unit->min = minBuf[0];
    unit->alarm = alarmBuf[0];

    unit->crMin = crMinBuf[0];
    unit->crMax = crMaxBuf[0];
}

/**
 * 数据初始化  测试用
 */
void init_data(_devDataObj *ptr)
{
    static ushort buf[LINE_NUM] = {200};
    static uint buf2[LINE_NUM] = {2*1000};
    static uchar swbuf[LINE_NUM] = {1};

    ptr->len = LINE_NUM;
    init_unit(&(ptr->cur));
    init_unit(&(ptr->vol));

    ptr->sw = swbuf;
    ptr->pow = buf2;
    ptr->ele = buf2;
    ptr->pf = buf;
}

/**
 * 初始化数据  Unit，
 */
void init_Unit(_devDataUnit *unit, sDataUnit *cUnit, int n)
{
    for(int i = 0; i < LINE_NUM; i++){
        valueBuf[n][i]  = (ushort)cUnit->value[i]; //;
        maxBuf[n][i]    = (ushort)cUnit->max[i];
        minBuf[n][i]    = (ushort)cUnit->min[i];
        alarmBuf[n][i]  = (uchar)cUnit->alarm[i];
        crMinBuf[n][i]  = (ushort)cUnit->crMin[i];
        crMaxBuf[n][i]  = (ushort)cUnit->crMax[i];
    }

    unit->value = valueBuf[n];
    unit->max = maxBuf[n];
    unit->min = minBuf[n];
    unit->alarm = alarmBuf[n];

    unit->crMin = crMinBuf[n];
    unit->crMax = crMaxBuf[n];
}
/**
 * 数据初始化  -- 相
 */
void init_dataLine(_devDataObj *ptr, sObjData *obj)
{
    static uchar swBuf[LINE_NUM] = {1};
    static uint powBuf[LINE_NUM] = {2*1000};
    static uint eleBuf[LINE_NUM] = {2*1000};
    static ushort pfBuf[LINE_NUM] = {200};
    static ushort apPowBuf[LINE_NUM] = {2*1000};
    static ushort waveBuf[LINE_NUM] = {2*1000};


    for(int i = 0; i < LINE_NUM; i++){
        swBuf[i]    = (uchar)obj->sw[i];
        powBuf[i]   = (uint)obj->pow[i];
        eleBuf[i]   = (uint)obj->ele[i];
        pfBuf[i]    = (ushort)obj->pf[i];
        apPowBuf[i] = (ushort)obj->apPow[i];
        waveBuf[i]  = (ushort)obj->wave[i];
    }

    ptr->len = LINE_NUM;
    init_Unit(&(ptr->vol), &(obj->vol), 0);
    init_Unit(&(ptr->cur), &(obj->cur), 1);


    ptr->sw    = swBuf;   //开关状态
    ptr->pow   = powBuf;  // 功率
    ptr->ele   = eleBuf;  // 电能
    ptr->pf    = pfBuf;   //功率因素
    ptr->apPow = apPowBuf; //视在功率
    ptr->wave  = waveBuf;  // 谐波值

}


void sent_str(int id, int fn1, int fn2, short len, char *str)
{
    dev_data_packet msg;
    msg.addr = id;
    msg.len = len;
    msg.data = (uchar *)str;

    msg.fn[0] = fn1;
    msg.fn[1] = fn2;
    data_packet_sent(&msg);
}



void sent_busName(void)
{
    dev_data_packet msg;
    msg.num = 0;
    msg.addr = 0;

    msg.len = 3;  //=======
    msg.data = (uchar *)"bus";

    msg.fn[0] = 5;
    msg.fn[1] = 0x11;
    data_packet_sent(&msg);
}

void sent_busRateCur(void)
{
    dev_data_packet msg;
    msg.num = 0;
    msg.addr = 0;

    uchar data[2] = {0, 200};

    msg.len = 2;  //=======
    msg.data = data;

    msg.fn[0] = 30;
    msg.fn[1] = 0;
    data_packet_sent(&msg);
}

void sent_busBoxNum(void)
{
    dev_data_packet msg;
    msg.num = 0;
    msg.addr = 0;

    uchar data[2] = {16};

    msg.len = 1;  //=======
    msg.data = data;

    msg.fn[0] = 31;
    msg.fn[1] = 0;
    data_packet_sent(&msg);
}

/**
 * 发送测试数据， 测试用
 */
void sent_dev_data(void)
{
    qDebug() << currentBus;

    uchar id = currentBus - '0';
    sDataPacket *shm = get_share_mem(); // 获取共享内存
    int len = shm->data[id].boxNum + 1;  //始端箱也算
    for(int  i=0; i< len; ++i) {

        if(shm->data[id].box[i].offLine < 1) continue; //不在线就跳过

        pduDevData *devData = (pduDevData*)malloc(sizeof(pduDevData)); //申请内存
        memset(devData, 0, sizeof(pduDevData));
        sObjData *obj = &(shm->data[id].box[i].data);
        _devDataObj *ptr  = &(devData->line);
        init_dataLine(ptr, obj);  //输出位
        devData->env.len = LINE_NUM;
        sEnvData *env = &(shm->data[id].box[i].env);
        init_Unit(&(devData->env.tem), &(env->tem), 2); //温度
        // init_unit(&(devData->env.hum));

        sent_devData(i,devData);
        //sent_str(i, 6, 0x11, strlen(str), str);
        free(devData);
    }

    sent_busName();
    sent_busRateCur();
    sent_busBoxNum();
}






