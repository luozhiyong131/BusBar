#include "bus_boxlooptablewid.h"

BUS_BoxLoopTableWid::BUS_BoxLoopTableWid(QWidget *parent) : ComTableWid(parent)
{
    mPacket = nullptr;
    initWid();
}

void BUS_BoxLoopTableWid::initWid()
{
    QString title = tr("各回路信息");
    QStringList header;
    header <<tr("回路") <<tr("名称") <<tr("开关") << tr("电压") << tr("电流")
          << tr("功率") << tr("功率因素") << tr("电能");// << tr("温度");

    initTableWid(header, 1, title);
}

void BUS_BoxLoopTableWid::initFun(int bus, int box)
{
    mPacket = BUS_DataPackets::bulid()->getBox(bus, box);
}

void BUS_BoxLoopTableWid::setAlarm(sObjData *unit, int row)
{
    int column=2, swAlarm=0;

    int value = unit->sw;
    if(value != 1) swAlarm = 2;
    setItemColor(row, column++, swAlarm);

    value = unit->vol.alarm;
    if(value) value = 2;
    setItemColor(row, column++, value);

    value = unit->cur.alarm;
    if(value) value = 2;
    else value = unit->cur.crAlarm;
    setItemColor(row, column++, value);
}

void BUS_BoxLoopTableWid::setObjUnit(sObjData *unit, QStringList &list)
{
    QString  str = tr("断开");;
    if(unit->sw ) str = tr("接通");
    list << str;

    str = "---";
    double value = unit->vol.value /COM_RATE_VOL;
    if(value > 0) str = QString::number(value) + "V";
    list << str;

    value = unit->cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    if(unit->pow) {
        value = unit->pow / COM_RATE_POW;
        list << QString::number(value) + "KW";
    } else {
        value = unit->activePow / COM_RATE_POW;
        list << QString::number(value) + "KVA";
    }

    if(unit->pf) {
        value = unit->pf / COM_RATE_PF;
        list << QString::number(value);
    } else {
        list << "---";
    }

    value = unit->ele / COM_RATE_ELE;
    list << QString::number(value) + "KWh";
}

int BUS_BoxLoopTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int num = dev->data.loopNum;
        for(int i=0; i<num; ++i)
        {
            QStringList list;
            if(dev->dc)  list << QString((char)('A' + i%3))+ QString("%1").arg(i/3 + 1);
            else list << "D" + QString("%1").arg(i + 1);

            sObjData *obj = &(dev->data.loop[i]);
            list << obj->name;

            setObjUnit(obj,  list);
            setAlarm(obj,  row);
            setTableRow(row++, list);
        }
    }

    return row;
}

/**
 * @brief 数据更新入口函数
 */
void BUS_BoxLoopTableWid::updateData()
{
    int row = 0;

    if(mPacket) {
        row = updateDev(mPacket, row);
    } else {
        qDebug() << "mPackets is NULL";
    }

    checkTableRow(row);
}

void BUS_BoxLoopTableWid::timeoutDone()
{
    updateData();
}
