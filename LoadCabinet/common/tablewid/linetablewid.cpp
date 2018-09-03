/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "linetablewid.h"

LineTableWid::LineTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void LineTableWid::initWid()
{
    QString title = tr("设备实时相信息");
    QStringList header;
    header << tr("设备号") << tr("相数")  << tr("开关")
           << tr("电压") << tr("电流") << tr("功率")
           << tr("功率因素") << tr("电能");
    initTableWid(header, 1, title);
}

void LineTableWid::setAlarm(sObjData &unit, int row)
{
    int column=2, swAlarm=0;

    int value = unit.sw;
    if(value != 1) swAlarm = 2;
    setItemColor(row, column++, swAlarm);

    value = unit.vol.alarm;
    if(value) value = 2;
    setItemColor(row, column++, value);

    value = unit.cur.alarm;
    if(value) value = 2;
    else value = unit.cur.crAlarm;
    setItemColor(row, column++, value);
}

void LineTableWid::setObjUnit(sObjData &unit, QStringList &list)
{
    QString  str = tr("断开");;
    if(unit.sw == mSwValue) {
        str = tr("闭合");
    }
    list << str;

    str = "---";
    double value = unit.vol.value / COM_RATE_VOL;
    if(value > 0) str = QString::number(value) + "V";
    list << str;

    value = unit.cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    if(unit.pow) {
        value = unit.pow / COM_RATE_POW;
        list << QString::number(value) + "KW";
    } else {
        value = unit.activePow / COM_RATE_POW;
        list << QString::number(value) + "KVA";
    }

    if(unit.pf) {
        value = unit.pf / COM_RATE_PF;
        list << QString::number(value);
    } else {
        list << "---";
    }

    value = unit.ele / COM_RATE_ELE;
    list << QString::number(value) + "KWh";
}

int LineTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int line = dev->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            QString str = dev->data.line[i].name;
            if(str.isEmpty()) list << ("L "+QString::number(i+1));

            setObjUnit(dev->data.line[i],  list);
            setAlarm(dev->data.line[i],  row);
            setTableRow(row++, list);
        }
    }

    return row;
}

/**
 * @brief 数据更新入口函数
 */
void LineTableWid::updateData()
{
    int row = 0;

    if(mPackets) {
        for(int i=1; i<=mPackets->devNum; ++i)
        {
            sDataPacket *dev = &(mPackets->dev[i]);
            row = updateDev(dev, row);
        }
    } else {
        qDebug() << "mPackets is NULL";
    }

    checkTableRow(row);
}

void LineTableWid::timeoutDone()
{
    updateData();
}
