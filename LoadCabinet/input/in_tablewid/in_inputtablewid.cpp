#include "in_inputtablewid.h"

IN_InputTableWid::IN_InputTableWid(QWidget *parent) : LineTableWid(parent)
{
    initWid();
}


void IN_InputTableWid::initWid()
{
    QString title = tr("设备输出位实时相信息");
    QStringList header;
    header << tr("设备号") << tr("输出位")  << tr("开关")
           << tr("电压") << tr("电流") << tr("功率")
           << tr("功率因素") << tr("电能");
    initTableWid(header, 1, title);
}


int IN_InputTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int line = dev->data.outputNum;
        for(int i=0; i<line; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            QString str = dev->data.output[i].name;
            if(str.isEmpty()) list << ("Output "+QString::number(i+1));

            setObjUnit(dev->data.output[i],  list);
            setAlarm(dev->data.output[i],  row);
            setTableRow(row++, list);
        }
    }

    return row;
}
