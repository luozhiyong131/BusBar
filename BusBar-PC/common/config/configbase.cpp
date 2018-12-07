/*
 * 配置文件公共基类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "configbase.h"

ConfigBase::ConfigBase()
{
//    item = new sConfigItem();
}


/**
 * @brief 获取串口名称
 * @return 串口名
 */
QString ConfigBase::getSerialName(int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM_%2").arg(prefix).arg(id);
    return sys_configFile_readStr(str, prefix);
}

/**
 * @brief 设置串口名
 * @param name
 */
void ConfigBase::setSerialName(const QString &name, int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM_%2").arg(prefix).arg(id);
    sys_configFile_writeParam(str, name, prefix);
}



/**
 * @brief 获取串口名称
 * @return 串口名
 */
QString ConfigBase::getIp(int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_ip_%2").arg(prefix).arg(id);
    return sys_configFile_readStr(str, prefix);
}

/**
 * @brief 设置串口名
 * @param name
 */
void ConfigBase::setIp(const QString &ip, int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_ip_%2").arg(prefix).arg(id);
    sys_configFile_writeParam(str, ip, prefix);
}


/**
 * @brief 获取级联数量
 * @return
 */
int ConfigBase::getDevNum( int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_devnum_%2").arg(prefix).arg(id);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;

    return ret;
}

/**
 * @brief 设置级联数据
 * @param num
 */
void ConfigBase::setDevNum(int num, int id)
{
    QString prefix = getPrefix();
    QString str = QString("%1_devnum_%2").arg(prefix).arg(id);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}


/**
 * @brief 获取Modbus命令模式的模式
 * @return
 */
int ConfigBase::getModbusCmd()
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_cmd").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;
    return ret;
}

/**
 * @brief 设置Modbus命令模
 * @param num
 */
void ConfigBase::setModbusCmd(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_cmd").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}

/**
 * @brief 获取Modbus 传输时间间隔Time
 * @return
 */
int ConfigBase::getModbusTime()
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_time").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;
    return ret;
}

/**
 * @brief 设置Modbus 传输时间间隔Time
 * @return
 */
void ConfigBase::setModbusTime(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_time").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}

/**
 * @brief 获取日志存储时间隔
 * @return
 */
int ConfigBase::getLogTime()
{
    QString prefix = getPrefix();
    QString str = QString("%1_log_time").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 60;
    return ret;
}

/**
 * @brief 设置日志存储时间间隔
 * @param num
 */
void ConfigBase::setLogTime(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_log_time").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}

