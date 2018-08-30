#include "in_envtablewid.h"

IN_EnvTableWid::IN_EnvTableWid(QWidget *parent) : LineTableWid(parent)
{
    initWid();
}


void IN_EnvTableWid::initWid()
{
    QString title = tr("设备环境信息");
    QStringList header;
    header << tr("设备号") << tr("传感器")
           << tr("温度") << tr("温度下限") << tr("温度上限");
    initTableWid(header, 1, title);
}


void IN_EnvTableWid::setAlarm(sEnvData &unit, int id, int row)
{
    int value = unit.tem[id].alarm;
    if(value) value = 2;
    setItemColor(row, 2, value);
}


void IN_EnvTableWid::setObjUnit(sEnvData &unit, int id, QStringList &list)
{
    double value = unit.tem[id].value / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem[id].min / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem[id].max / COM_RATE_TEM;
    list << QString::number(value) + " ℃";
}


int IN_EnvTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int num = dev->data.env.envNum;
        for(int i=0; i<num; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            list << tr("传感器 %1").arg(i+1);
            setObjUnit(dev->data.env, i,  list);
            setAlarm(dev->data.env, i,  row);
            setTableRow(row++, list);
        }
    }

    return row;
}

