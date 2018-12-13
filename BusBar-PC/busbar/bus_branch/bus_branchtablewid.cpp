#include "bus_branchtablewid.h"

BUS_BranchTableWid::BUS_BranchTableWid(QWidget *parent) : ComTableWid(parent)
{
    initFun(0);
    initWid();
}

void BUS_BranchTableWid::initWid()
{
    QString title = tr("各支路信息");
    QStringList header;
    header <<tr("插接箱") << tr("状态") << tr("A电流") << tr("A电能")
          << tr("B电流") << tr("B电能") << tr("C电流")   << tr("C电能");

    initTableWid(header, 1, title);
}


void BUS_BranchTableWid::initFun(int bus)
{
    mBusID = bus;
    mPackets = BUS_DataPackets::bulid()->getBus(bus);
}


void BUS_BranchTableWid::setObjUnit(sObjData *unit, QStringList &list)
{
    QString  str = "---";
    double  value = unit->cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit->ele / COM_RATE_ELE;
    list << QString::number(value) + "KWh";
}

QString BUS_BranchTableWid::setAlarm(sDataPacket *dev, int row)
{
    int alarm = 2;
    QString str = tr("正常");
    if(dev->offLine) {
        if(dev->alarm) str = tr("告警");
        else alarm = 0;
    } else {
        str = tr("离线");
    }
    setItemColor(row, 1, alarm);

    return str;
}

int BUS_BranchTableWid::updateDev(sDataPacket *dev, int row)
{
    QStringList list;
    list << dev->name;
    list << setAlarm(dev, row);

    int num = dev->data.lineNum;
    for(int i=0; i<num; ++i) {
        sObjData *obj = &(dev->data.line[i]);
        setObjUnit(obj,  list);
    }
    setTableRow(row++, list);

    return row;
}


/**
 * @brief 数据更新入口函数
 */
void BUS_BranchTableWid::updateData()
{
    int row = 0;

    if(mPackets) {
        for(int i=1; i<=mPackets->devNum; ++i) {
            sDataPacket *dev = &(mPackets->dev[i]);
            row = updateDev(dev, row);
        }
    } else {
        qDebug() << "mPackets is NULL";
    }

    checkTableRow(row);
}

void BUS_BranchTableWid::timeoutDone()
{
    updateData();
}

void BUS_BranchTableWid::busChangeSlot(int id)
{
    initFun(id);
}

void BUS_BranchTableWid::itemDoubleClicked(QTableWidgetItem* )
{
    int row = currentRow();

    BUS_BoxDlg dlg(this);
    dlg.initBox(mBusID, row+1);
    dlg.exec();
}
