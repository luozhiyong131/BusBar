#include "logdevwid.h"

LogDevWid::LogDevWid(QWidget *parent) : LogComEleWid(parent)
{

}


QString LogDevWid::getTableName()
{
    return  DbDevEle::bulid()->tableName();
}

void LogDevWid::initTable()
{
    QString table = getTableName();
    this->refreshTable(table);

    QStringList headList;
    headList << tr("编号") << tr("日期") << tr("时间") <<tr("设备")<< tr("电压")<< tr("电流") << tr("功率") << tr("电能");
    model->setHeaders(headList);
}
