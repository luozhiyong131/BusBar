#include "setlooptemwid.h"
#include <QGridLayout>

SetLoopTemWid::SetLoopTemWid(QWidget *parent) : ComTableWid(parent)
{
    checkBus(0);
    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}


void SetLoopTemWid::initWid()
{
    QString title = tr("温度");
    QStringList header;
    header<< tr("插接箱");

    for(int i=0; i<SENOR_NUM; ++i)
        header << tr("温度") + QString::number(i+1);

    initTableWid(header, 1, title);
}


void SetLoopTemWid::checkBus(int index)
{
     mBus = index;
     mPackets = BUS_DataPackets::bulid()->getBus(mBus);
}


int SetLoopTemWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        QStringList list;
        list << dev->name;

        for(int i=0; i<SENOR_NUM; ++i)
        {
            sDataUnit *unit = &(dev->data.env.tem[i]);
            double value = unit->value / COM_RATE_TEM;
            list <<  QString::number(value) + "℃";
            setItemColor(row, i+1, unit->alarm);
        }

        setTableRow(row, list);
    }

    return ++row;
}

/**
 * @brief 数据更新入口函数
 */
void SetLoopTemWid::updateData()
{
    int row = 0;

    for(int i=1; i<=mPackets->devNum; ++i)
    {
        sDataPacket *box = &(mPackets->dev[i]);
        row = updateDev(box, row);
    }

    checkTableRow(row);
}

void SetLoopTemWid::timeoutDone()
{
    checkBus(mBus);
    updateData();
}


void SetLoopTemWid::itemClicked(QTableWidgetItem *it)
{
    if(it->text().compare("---") == 0) return;  //为空不设置
    int column = it->column();
    if(column > 0)
    {
        sThresholdItem item;
        item.bus = mBus;
        item.box = it->row()+1;
        item.num = column-1;
        item.type = 3;

        SetThresholdDlg dlg(this);
        dlg.set(item);
        dlg.exec();
    }
}
