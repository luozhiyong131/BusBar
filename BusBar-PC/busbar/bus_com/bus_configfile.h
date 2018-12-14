#ifndef BUS_CONFIGFILE_H
#define BUS_CONFIGFILE_H
#include "configbase.h"
#define BUS_NUM 4  // 四条母线

struct BUS_sConfigItem : public sConfigItem
{
    QString ips[BUS_NUM];
    SerialPort *serials[BUS_NUM]; // 串口对象
    QString comNames[BUS_NUM];
    int devNums[BUS_NUM]; // 级联数
};


class BUS_ConfigFile : public ConfigBase
{
    BUS_ConfigFile();
public:
    static BUS_ConfigFile *bulid();
    BUS_sConfigItem *mItem;

    void save();
protected:
    void init();
    QString getPrefix(){return "bus";}
};

QString bus_getPassword();

#endif // BUS_CONFIGFILE_H
