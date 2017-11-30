#include "logcabelewid.h"

LogCabEleWid::LogCabEleWid(QWidget *parent) : LogComEleWid(parent)
{

}


QString LogCabEleWid::getTableName()
{
    return  DbCabEle::bulid()->tableName();
}

void LogCabEleWid::initTable()
{
    QString table = getTableName();
    this->refreshTable(table);

    QStringList headList;
    headList << tr("编号") << tr("日期") << tr("时间") << tr("电压")<< tr("电流") << tr("功率") << tr("电能");
    model->setHeaders(headList);
}


void LogCabEleWid::clearTableSlot()
{
    model->model->setTable("markingtable");
    DbCabEle* db = DbCabEle::bulid();
    db->clear();
    db->createTable();
    initTable();
//    if(model->removeRow(0))
//        QTimer::singleShot(10,this,SLOT(clearTableSlot()));
}
