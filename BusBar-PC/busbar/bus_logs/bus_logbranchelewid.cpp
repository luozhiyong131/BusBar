#include "bus_logbranchelewid.h"

BUS_LogBranchEleWid::BUS_LogBranchEleWid(QWidget *parent) : BUS_LogLineEleWid(parent)
{

}

BasicSql *BUS_LogBranchEleWid::getDb()
{
    return  bus_branchEle_db(mId);
}

/**
 * @brief 初始化表格
 */
void BUS_LogBranchEleWid::initTable()
{
    setTableSlot(mId);

    mTableTile = "BUS " + tr("支路电能");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("插接箱");
    mHeadList << tr("A1/D1") << tr("B1/D2") << tr("C1/D3") << tr("A2/D4") << tr("B2")
              << tr("C2") << tr("A3") << tr("B3") << tr("C3");
    mHeadList << tr("合计");
    model->setHeaders(mHeadList);
}
