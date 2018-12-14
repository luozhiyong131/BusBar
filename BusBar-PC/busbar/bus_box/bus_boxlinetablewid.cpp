#include "bus_boxlinetablewid.h"

BUS_BoxLineTableWid::BUS_BoxLineTableWid(QWidget *parent) : BUS_BoxLoopTableWid(parent)
{
    initWid();
}

void BUS_BoxLineTableWid::initWid()
{
    QString title = tr("各相信息");
    QStringList header;
    header <<tr("名称") << tr("电压") << tr("电流") << tr("负载率") << tr("电流谐波含量")
          << tr("视在功率") << tr("有功功率") << tr("功率因素") << tr("电能") << tr("温度");

    initTableWid(header, 1, title);
}

void BUS_BoxLineTableWid::setAlarm(sObjData *unit, int row)
{
    int column=1;

    int value = unit->vol.alarm;
    if(value) value = 2;
    setItemColor(row, column++, value);

    value = unit->cur.alarm;
    if(value) value = 2;
    else value = unit->cur.crAlarm;
    setItemColor(row, column++, value);
}

void BUS_BoxLineTableWid::setTemAlarm(sDataUnit *unit, int row)
{
    int column=9;

    int value = unit->alarm;
    if(value) value = 2;
    setItemColor(row, column++, value);
}

void BUS_BoxLineTableWid::setObjUnit(sObjData *unit, QStringList &list)
{
    QString  str = "---";
    double value = unit->vol.value /COM_RATE_VOL;
    if(value > 0) str = QString::number(value) + "V";
    list << str;

    value = unit->cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit->pl / COM_RATE_PF;
    list << QString::number(value) + "%";

    value = unit->curThd / COM_RATE_PF;
    list << QString::number(value) + "%";

    value = unit->pow / COM_RATE_POW;
    list << QString::number(value) + "KW";

    value = unit->activePow / COM_RATE_POW;
    list << QString::number(value) + "KVA";

    value = unit->pf / COM_RATE_PF;
    list << QString::number(value);

    value = unit->ele / COM_RATE_ELE;
    list << QString::number(value) + "KWh";
}

int BUS_BoxLineTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int num = dev->data.lineNum;
        for(int i=0; i<num; ++i)
        {
            QStringList list;
            if(dev->dc)  list << QString((char)('A' + i%3))+ QString("%1").arg(i/3 + 1);
            else list << "D" + QString("%1").arg(i + 1);

            sObjData *obj = &(dev->data.line[i]);
            list << obj->name;

            setObjUnit(obj,  list);
            setAlarm(obj,  row);

            sDataUnit *unit = &(dev->data.env.tem[i]);
            double value =unit->value / COM_RATE_TEM;
            list << QString::number(value) + "C";
            setTemAlarm(unit, row);

            setTableRow(row++, list);
        }
    }

    return row;
}
