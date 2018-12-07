#ifndef CONFIGBASH
#define CONFIGBASH
#include "sysconfigfile.h"
#include "serialportdlg.h"



struct sConfigItem
{
    sConfigItem() {logMins=60; msecs=5; cmdModel=2;}

    int msecs;
    int cmdModel; // 命令模式
    int logMins; // 日志间隔时间分钟
};

class ConfigBase
{
public:
    ConfigBase();
//    sConfigItem *item;

    QString getSerialName(int id=0);
    void setSerialName(const QString &name, int id=0);

    QString getIp(int id=0);
    void setIp(const QString &ip,int id=0);

    int getDevNum(int id=0);
    void setDevNum(int num, int id=0);

    int getModbusCmd();
    void setModbusCmd(int num);

    int getModbusTime();
    void setModbusTime(int num);

    int getLogTime();
    void setLogTime(int num);

    virtual QString getPrefix()=0;
};

#endif // CONFIGBASH
