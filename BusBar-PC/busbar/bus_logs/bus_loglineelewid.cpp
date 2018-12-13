#include "bus_loglineelewid.h"

BUS_LogLineEleWid::BUS_LogLineEleWid(QWidget *parent) : BUS_LogAlarmWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *BUS_LogLineEleWid::getDb()
{
    return  bus_lineEle_db(mId);
}

/**
 * @brief 初始化表格
 */
void BUS_LogLineEleWid::initTable()
{
    setTableSlot(mId);

    mTableTile = "BUS " + tr("主路电能");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("A")<< tr("B") << tr("C") << tr("合相");
    model->setHeaders(mHeadList);
}
