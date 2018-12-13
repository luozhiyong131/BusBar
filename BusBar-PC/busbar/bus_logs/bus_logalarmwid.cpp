#include "bus_logalarmwid.h"

BUS_LogAlarmWid::BUS_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{
    mId = 0;
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *BUS_LogAlarmWid::getDb()
{
    return  bus_alarm_db(mId);
}

/**
 * @brief 初始化表格
 */
void BUS_LogAlarmWid::initTable()
{
    setTableSlot(mId);

    mTableTile = "BUS " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("告警项目")<< tr("告警内容") ;
    model->setHeaders(mHeadList);
}

void BUS_LogAlarmWid::setTableSlot(int id)
{
    mId = id;
    QString table = getDb()->tableName();
    this->refreshTable(table);
}
