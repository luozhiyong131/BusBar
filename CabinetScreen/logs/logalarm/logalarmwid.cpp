#include "logalarmwid.h"

LogAlarmWid::LogAlarmWid(QWidget *parent) : LogComEleWid(parent)
{

}


QString LogAlarmWid::getTableName()
{
    return  DbAlarm::bulid()->tableName();
}

void LogAlarmWid::initTable()
{
    QString table = getTableName();
    this->refreshTable(table);

    QStringList headList;
    headList << tr("编号") << tr("日期") << tr("时间") << tr("报警项目")<< tr("报警内容") ;
    model->setHeaders(headList);
}


void LogAlarmWid::clearTableSlot()
{
#if SQL_DEL_MODE
    model->model->setTable("markingtable");
    DbAlarm* db = DbAlarm::bulid();
    db->clear();
    db->createTable();
    initTable();
#else
    if(model->removeRow(0))
        QTimer::singleShot(10,this,SLOT(clearTableSlot()));
#endif
}
