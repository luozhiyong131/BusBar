#include "setloopwid.h"

SetLoopWid::SetLoopWid(QWidget *parent) : ComTableWid(parent)
{
    mDc = 1;
    checkBus(0);
    initWid();
}


void SetLoopWid::initWid()
{
    QString title = tr("回路电流");
    QStringList header;
    header<< tr("插接箱");

    if(mDc){ //交流9个
        for(int i = 0; i < LOOP_NUM; ++i)
            header << QString((char)('A' + i%3))+ QString("%1").arg(i/3 + 1);
    }else{ //直流4个
        for(int i = 0; i < 4; i++)
            header << "D" + QString("%1").arg(i + 1);
    }

    initTableWid(header, 1, title);
}



void SetLoopWid::checkBus(int index)
{
    mBus = index;
    mPackets = BUS_DataPackets::bulid()->getBus(mBus);

    int dc = mPackets->dev[0].dc;
    if(mDc != dc ) {
        mDc = dc;
        initWid();
    }
}


int SetLoopWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        QStringList list;
        list << dev->name;

        int line = dev->data.loopNum;
        for(int i=0; i<line; ++i)
        {
            sDataUnit *unit = &(dev->data.loop[i].cur);
            double value = unit->value / COM_RATE_CUR;
            list << QString::number(value,'f', 1) + "A";
            setItemColor(row, i+1, unit->alarm);
        }

        setTableRow(row, list);
    }

    return ++row;
}

/**
 * @brief 数据更新入口函数
 */
void SetLoopWid::updateData()
{
    int row = 0;

    for(int i=1; i<=mPackets->devNum; ++i)
    {
        sDataPacket *box = &(mPackets->dev[i]);
        row = updateDev(box, row);
    }

    checkTableRow(row);
}

void SetLoopWid::timeoutDone()
{
    checkBus(mBus);
    updateData();
}


void SetLoopWid::itemClicked(QTableWidgetItem *it)
{
    if(it->text().compare("---") == 0) return;  //为空不设置
    static int i = 0;//防止弹出多次对话框
    i++;
    if(i % 3 == 1)
    {

        int column = it->column();
        if(column > 0)
        {
            sThresholdItem item;
            item.bus = mBus;
            item.box = it->row()+1;
            item.num = column-1;
            item.type = 2;

            SetThresholdDlg dlg(this);
            dlg.set(item);
            dlg.exec();
            i = 1;
        }
    }
}
