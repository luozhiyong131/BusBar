/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_inputthresholdtablewid.h"

IN_InputThresholdTableWid::IN_InputThresholdTableWid(QWidget *parent) : IN_InputTableWid(parent)
{
     initWid();
}


void IN_InputThresholdTableWid::initWid()
{
    QString title = tr("设备输入位阈值信息");
    QStringList header;
    header << tr("设备号") << tr("输入位")
           << tr("电压") << tr("电压下限") << tr("电压上限")
           << tr("电流") << tr("电流下限") << tr("电流上限");
    initTableWid(header, 1, title);
}


void IN_InputThresholdTableWid::setAlarm(sObjData &unit, int row)
{
    int value = unit.vol.alarm;
    if(value) value = 2;
    setItemColor(row, 2, value);

    value = unit.cur.alarm;
    if(value) value = 2;
    else value = unit.cur.crAlarm;
    setItemColor(row, 5, value);
}


void IN_InputThresholdTableWid::setObjUnit(sObjData &unit, QStringList &list)
{
    double value = unit.vol.value / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.min / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.max / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.min / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.max / COM_RATE_CUR;
    list << QString::number(value) + "A";
}
