#include "setbox.h"

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

void SetBOXThread::setItemInit(DbThresholdItem item)
{
    mItem = item;
}

bool SetBOXThread::send(int runType)
{
    if(isRunType != 0) return false;
    isRunType = runType;
    start();
    return true;
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

int SetBOXThread::transmit(int addr, ushort reg, ushort len)
{
    return rtu[mBusID]->transmit(addr, reg, len);
}

int SetBOXThread::sendData(int addr, ushort reg, ushort len)
{
    return rtu[mBusID]->sendData(addr, reg, len);
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

    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度 6 回路电压阈值
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
    qDebug() <<  sendData(boxNum, addrMin[num], item.min);
    qDebug() <<  sendData(boxNum, addrMax[num], item.max);
    return ret;
}

void SetBOXThread::saveAllItem(DbThresholdItem &item)
{
    int boxNum=0, num = item.num;
    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度 6 回路电压阈值
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
    qDebug() << "lenAll" << boxNum << num << item.type;
    return;

    switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度 6 回路电压阈值
    {
    case 1: setLineVolAll(item);  break; //主路电压阈值
    case 2: setLineCurAll(item);  break; //主路电流阈值
    case 3: setLoopCurAll(item);  break; //回路电流阈值
    case 4: setLineTempAll(item); break; //始端箱温度
    case 5: setTempAll(item);     break; //插接箱温度
    case 6: break;
    }
}

void SetBOXThread::setLoopCurAll(DbThresholdItem &item)
{

}

void SetBOXThread::setTempAll(DbThresholdItem &item)
{

}

void SetBOXThread::setLineVolAll(DbThresholdItem &item)
{

}

void SetBOXThread::setLineCurAll(DbThresholdItem &item)
{

}

void SetBOXThread::setLineTempAll(DbThresholdItem &item)
{

}

