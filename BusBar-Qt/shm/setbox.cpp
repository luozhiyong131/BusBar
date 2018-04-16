#include "setbox.h"

#define TIME 6000

SetBOXThread::SetBOXThread(QObject *parent)
{
    mBusID = 0;
    isRunType = 0;
}

SetBOXThread *SetBOXThread::bulid()
{
    static SetBOXThread* sington = NULL;
    if(sington == NULL)
        sington = new SetBOXThread();
    return sington;
}

bool SetBOXThread::send(int runType, DbThresholdItem item)
{
    mItem = item;

    if(isRunType != 0) return false;
    isRunType = runType;
    start();
    return true;
}

bool SetBOXThread::isRun()
{
    if(isRunType != 0) return true;
    return false;
}

void SetBOXThread::run()
{
    if(1 == isRunType){ //单元设置
        saveItem(mItem);
    }else if(2 == isRunType){ //统一设置
        saveAllItem(mItem);
    }else{

    }
    isRunType = 0;

}

void SetBOXThread::busChangedSlot(int cBusID)
{
    mBusID = cBusID;
}

int SetBOXThread::transmit(int addr, ushort reg, ushort len, int busID)
{
    if(busID == -1) busID = mBusID;
    if(rtu[busID] == NULL) return -1;
    return rtu[busID]->transmit(addr, reg, len);
}

int SetBOXThread::sendData(int addr, ushort reg, ushort len, int busID, bool value)
{
    if(busID == -1) busID = mBusID;
    if(rtu[busID] == NULL) return -1;
    return rtu[busID]->sendData(addr, reg, len, value);
}

bool SetBOXThread::saveItem(DbThresholdItem &item)
{
    bool ret = true;

    int boxNum=0, num = item.num;
    ushort addrMin[9], addrMax[9];

    if(item.type == 1 || item.type ==6){
        addrMax[0] = sSetType::VoltageMAX_L1;
        addrMax[1] = sSetType::VoltageMAX_L2;
        addrMax[2] = sSetType::VoltageMAX_L3;
        addrMax[3] = sSetType::VoltageMAX_L4;
        addrMax[4] = sSetType::VoltageMAX_L5;
        addrMax[5] = sSetType::VoltageMAX_L6;
        addrMax[6] = sSetType::VoltageMAX_L7;
        addrMax[7] = sSetType::VoltageMAX_L8;
        addrMax[8] = sSetType::VoltageMAX_L9;

        addrMin[0] = sSetType::VoltageMIN_L1;
        addrMin[1] = sSetType::VoltageMIN_L2;
        addrMin[2] = sSetType::VoltageMIN_L3;
        addrMin[3] = sSetType::VoltageMIN_L4;
        addrMin[4] = sSetType::VoltageMIN_L5;
        addrMin[5] = sSetType::VoltageMIN_L6;
        addrMin[6] = sSetType::VoltageMIN_L7;
        addrMin[7] = sSetType::VoltageMIN_L8;
        addrMin[8] = sSetType::VoltageMIN_L9;
    }else if(item.type == 2 || item.type ==3){
        addrMax[0] = sSetType::CurrentMAX_L1;
        addrMax[1] = sSetType::CurrentMAX_L2;
        addrMax[2] = sSetType::CurrentMAX_L3;
        addrMax[3] = sSetType::CurrentMAX_L4;
        addrMax[4] = sSetType::CurrentMAX_L5;
        addrMax[5] = sSetType::CurrentMAX_L6;
        addrMax[6] = sSetType::CurrentMAX_L7;
        addrMax[7] = sSetType::CurrentMAX_L8;
        addrMax[8] = sSetType::CurrentMAX_L9;

        addrMin[0] = sSetType::CurrentMIN_L1;
        addrMin[1] = sSetType::CurrentMIN_L2;
        addrMin[2] = sSetType::CurrentMIN_L3;
        addrMin[3] = sSetType::CurrentMIN_L4;
        addrMin[4] = sSetType::CurrentMIN_L5;
        addrMin[5] = sSetType::CurrentMIN_L6;
        addrMin[6] = sSetType::CurrentMIN_L7;
        addrMin[7] = sSetType::CurrentMIN_L8;
        addrMin[8] = sSetType::CurrentMIN_L9;
    }else if(item.type == 4 || item.type ==5){
        addrMax[0] = sSetType::temperatureMAX_1;
        addrMax[1] = sSetType::temperatureMAX_2;
        addrMax[2] = sSetType::temperatureMAX_3;

        addrMin[0] = sSetType::temperatureMIN_1;
        addrMin[1] = sSetType::temperatureMIN_2;
        addrMin[2] = sSetType::temperatureMIN_3;
    }

    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5接插箱温度 6 回路电压阈值
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        boxNum = num / LINE_NUM + 1;
        num = num % LINE_NUM ;
        break;
    case 4:
        break;
    case 5:
        boxNum = num / SENSOR_NUM + 1;
        num = num % SENSOR_NUM ;
        break;
    case 6:
        boxNum = num / LINE_NUM + 1;
        num = num % LINE_NUM ;
        break;
    }

    //----------------------[二分二路直流][显示]-----------------------[下面已做处理，取消——2018.3.21]
  /*  if(item.type == 3 || item.type ==6){  //交换2-3设置地址
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        sBusData *mBusData = &(shm->data[item.bus]);
        sBoxData *box = &(mBusData->box[boxNum]); //共享内存
        if(2 == box->rate && 2 == box->loopNum && 0 == box->dc){
           // swap(addrMin[1], addrMin[2]);
           // swap(addrMax[1], addrMax[2]);
            ushort  value;
            value = addrMin[2];
            addrMin[2] = addrMin[1];
            addrMin[1] = value;
            value = addrMax[2];
            addrMax[2] = addrMax[1];
            addrMax[1] = value;
        }
    } */
    //---------------------------------------------------------------

    if(sendData(boxNum, addrMin[num], item.min) > 0){
        msleep(TIME);
        sendData(boxNum, addrMax[num], item.max, item.bus, true);
    }
    return ret;
}

void SetBOXThread::saveAllItem(DbThresholdItem &item)
{
    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5接插箱温度 6 回路电压阈值
    {
        case 1: setLineVolAll(item);  break; //主路电压阈值
        case 2: setLineCurAll(item);  break; //主路电流阈值
        case 3: setLoopCurAll(item);  break; //回路电流阈值
        case 4: setLineTempAll(item); break; //始端箱温度
        case 5: setTempAll(item);     break; //接插箱温度
        case 6: break;
    }
}

void SetBOXThread::setLoopVolAll(DbThresholdItem &item)
{
    ushort addrMin[9], addrMax[9];
    addrMax[0] = sSetType::VoltageMAX_L1;
    addrMax[1] = sSetType::VoltageMAX_L2;
    addrMax[2] = sSetType::VoltageMAX_L3;
    addrMax[3] = sSetType::VoltageMAX_L4;
    addrMax[4] = sSetType::VoltageMAX_L5;
    addrMax[5] = sSetType::VoltageMAX_L6;
    addrMax[6] = sSetType::VoltageMAX_L7;
    addrMax[7] = sSetType::VoltageMAX_L8;
    addrMax[8] = sSetType::VoltageMAX_L9;

    addrMin[0] = sSetType::VoltageMIN_L1;
    addrMin[1] = sSetType::VoltageMIN_L2;
    addrMin[2] = sSetType::VoltageMIN_L3;
    addrMin[3] = sSetType::VoltageMIN_L4;
    addrMin[4] = sSetType::VoltageMIN_L5;
    addrMin[5] = sSetType::VoltageMIN_L6;
    addrMin[6] = sSetType::VoltageMIN_L7;
    addrMin[7] = sSetType::VoltageMIN_L8;
    addrMin[8] = sSetType::VoltageMIN_L9;

    for(int id=0; id<BUS_NUM; ++id)
    {
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        //--------------[广播]--------------------[试用]
        int lens;
        if(shm->data[id].box[0].dc){
            lens = LINE_NUM_MAX; //交流
        }else{
            lens = 4; //直流
        }

        for(int num=0; num < lens; ++num)
        {
            sendData(0xFF, addrMax[num], item.max, id, true);
            msleep(TIME);
            sendData(0xFF, addrMin[num], item.min, id, true);
        }

    }
}

void SetBOXThread::setLoopCurAll(DbThresholdItem &item)
{
    ushort addrMin[9], addrMax[9];
    addrMax[0] = sSetType::CurrentMAX_L1;
    addrMax[1] = sSetType::CurrentMAX_L2;
    addrMax[2] = sSetType::CurrentMAX_L3;
    addrMax[3] = sSetType::CurrentMAX_L4;
    addrMax[4] = sSetType::CurrentMAX_L5;
    addrMax[5] = sSetType::CurrentMAX_L6;
    addrMax[6] = sSetType::CurrentMAX_L7;
    addrMax[7] = sSetType::CurrentMAX_L8;
    addrMax[8] = sSetType::CurrentMAX_L9;

    addrMin[0] = sSetType::CurrentMIN_L1;
    addrMin[1] = sSetType::CurrentMIN_L2;
    addrMin[2] = sSetType::CurrentMIN_L3;
    addrMin[3] = sSetType::CurrentMIN_L4;
    addrMin[4] = sSetType::CurrentMIN_L5;
    addrMin[5] = sSetType::CurrentMIN_L6;
    addrMin[6] = sSetType::CurrentMIN_L7;
    addrMin[7] = sSetType::CurrentMIN_L8;
    addrMin[8] = sSetType::CurrentMIN_L9;

    for(int id=0; id<BUS_NUM; ++id)
    {
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        //--------------[广播]--------------------[试用]
        int lens;
        if(shm->data[id].box[0].dc){
            lens = LINE_NUM_MAX; //交流
        }else{
            lens = 4; //直流
        }

        for(int num=0; num < lens; ++num)
        {
            sendData(0xFF, addrMax[num], item.max, id, true);
            msleep(TIME);
            sendData(0xFF, addrMin[num], item.min, id, true);
        }

           //-------------[一套只能判断一次]-------------------
         /* int lens = LINE_NUM;
           if(0 == boxNum) lens = 3;
           int value = sendData(0, addrMax[0], item.max, id);
           if(value > 0){
                for(int num=0; num < lens; ++num)
                {
                    if(num != 0) sendData(0, addrMax[num], item.max, id, true);
                    msleep(TIME);
                    sendData(0, addrMin[num], item.min, id, true);
                }
            }*/
    }
}

void SetBOXThread::setTempAll(DbThresholdItem &item)
{
    ushort addrMin[9], addrMax[9];
    addrMax[0] = sSetType::temperatureMAX_1;
    addrMax[1] = sSetType::temperatureMAX_2;
    addrMax[2] = sSetType::temperatureMAX_3;
    addrMax[3] = sSetType::temperatureMAX_4;
    addrMax[4] = sSetType::temperatureMAX_5;
    addrMax[5] = sSetType::temperatureMAX_6;
    addrMax[6] = sSetType::temperatureMAX_7;
    addrMax[7] = sSetType::temperatureMAX_8;
    addrMax[8] = sSetType::temperatureMAX_9;

    addrMin[0] = sSetType::temperatureMIN_1;
    addrMin[1] = sSetType::temperatureMIN_2;
    addrMin[2] = sSetType::temperatureMIN_3;
    addrMin[3] = sSetType::temperatureMIN_4;
    addrMin[4] = sSetType::temperatureMIN_5;
    addrMin[5] = sSetType::temperatureMIN_6;
    addrMin[6] = sSetType::temperatureMIN_7;
    addrMin[7] = sSetType::temperatureMIN_8;
    addrMin[8] = sSetType::temperatureMIN_9;

    for(int id=0; id<BUS_NUM; ++id)
    {
        //-------------[区分交直流]--------- By_MW 2018.3.23
        sDataPacket *shm = get_share_mem(); // 获取共享内存
        sBusData *bus = &(shm->data[id]);
        int len;
        if(bus->box[0].dc){ //交流
            len = 3;
        }else{
            len = bus->box[0].rate;
        }
        //------------------------------
        //--------------[广播]--------------------[试用]
        for(int num=0; num < len; ++num)
        {
            sendData(0xFF, addrMax[num], item.max, id, true);
            msleep(TIME);
            sendData(0xFF, addrMin[num], item.min, id, true);
        }
       /* sDataPacket *shm = get_share_mem();id // 获取共享内存
        int len = shm->data[id].boxNum;
        for(int boxNum=0; boxNum<=len; ++boxNum)
        {
           int lens = SENSOR_NUM;
           if(0 == boxNum) lens = 3;
           //-------------[一套只能判断一次]-------------------
           int value = sendData(0, addrMax[0], item.max, id);
           if(value > 0){
                for(int num=0; num < lens; ++num)
                {
                    if(num != 0) sendData(boxNum, addrMax[num], item.max, id, true);
                    msleep(TIME);
                    sendData(boxNum, addrMin[num], item.min, id, true);
                }
            }
        }*/
    }
}

void SetBOXThread::setLineVolAll(DbThresholdItem &item)
{
    ushort addrMin[3], addrMax[3];
    addrMax[0] = sSetType::VoltageMAX_L1;
    addrMax[1] = sSetType::VoltageMAX_L2;
    addrMax[2] = sSetType::VoltageMAX_L3;

    addrMin[0] = sSetType::VoltageMIN_L1;
    addrMin[1] = sSetType::VoltageMIN_L2;
    addrMin[2] = sSetType::VoltageMIN_L3;

    for(int id=0; id<BUS_NUM; ++id)
    {
        //-------------[一套只能判断一次]-------------------
        int value = sendData(0, addrMax[0], item.max, id);
        if(value > 0){
            //-------------[区分交直流]--------- By_MW 2018.3.23
            sDataPacket *shm = get_share_mem(); // 获取共享内存
            sBusData *bus = &(shm->data[id]);
            int len;
            if(bus->box[0].dc){ //交流
                len = 3;
            }else{
                len = bus->box[0].rate;
            }
            //------------------------------
            for(int num=0; num<3; num++)
            {
                if(num != 0) sendData(0, addrMax[num], item.max, id, true);
                msleep(TIME);
                sendData(0, addrMin[num], item.min, id, true);
            }
        }
    }
}

void SetBOXThread::setLineCurAll(DbThresholdItem &item)
{
    ushort addrMin[3], addrMax[3];
    addrMax[0] = sSetType::CurrentMAX_L1;
    addrMax[1] = sSetType::CurrentMAX_L2;
    addrMax[2] = sSetType::CurrentMAX_L3;

    addrMin[0] = sSetType::CurrentMIN_L1;
    addrMin[1] = sSetType::CurrentMIN_L2;
    addrMin[2] = sSetType::CurrentMIN_L3;

    for(int id=0; id<BUS_NUM; ++id)
    {
        //-------------[一套只能判断一次]-------------------
        int value = sendData(0, addrMax[0], item.max, id);
        if(value > 0){
            //-------------[区分交直流]--------- By_MW 2018.3.23
            sDataPacket *shm = get_share_mem(); // 获取共享内存
            sBusData *bus = &(shm->data[id]);
            int len;
            if(bus->box[0].dc){ //交流
                len = 3;
            }else{
                len = bus->box[0].rate;
            }
            //------------------------------
            for(int num=0; num<len; num++)
            {
                if(num != 0) sendData(0, addrMax[num], item.max, id, true);
                msleep(TIME);
                sendData(0, addrMin[num], item.min, id, true);
            }
        }
    }
}

void SetBOXThread::setLineTempAll(DbThresholdItem &item)
{
    ushort addrMin[3], addrMax[3];
    addrMax[0] = sSetType::temperatureMAX_1;
    addrMax[1] = sSetType::temperatureMAX_2;
    addrMax[2] = sSetType::temperatureMAX_3;

    addrMin[0] = sSetType::temperatureMIN_1;
    addrMin[1] = sSetType::temperatureMIN_2;
    addrMin[2] = sSetType::temperatureMIN_3;

    for(int id=0; id<BUS_NUM; ++id)
    {
        //-------------[一套只能判断一次]-------------------
        int value = sendData(0, addrMax[0], item.max, id);
        if(value > 0){
            //-------------[区分交直流]--------- By_MW 2018.3.23
            sDataPacket *shm = get_share_mem(); // 获取共享内存
            sBusData *bus = &(shm->data[id]);
            int len;
            if(bus->box[0].dc){ //交流
                len = 3;
            }else{
                len = bus->box[0].rate;
            }
            //------------------------------

            for(int num = 0; num<len; num++)
            {
                if(num != 0) sendData(0, addrMax[num], item.max, id, true);
                msleep(TIME);
                sendData(0, addrMin[num], item.min, id, true);
            }
        }
    }
}







