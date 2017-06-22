/*
 * logalarmwid.cpp
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "logalarmwid.h"
#include "ui_logalarmwid.h"
#include "dbalarm.h"

LogAlarmWid::LogAlarmWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogAlarmWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

LogAlarmWid::~LogAlarmWid()
{
    delete ui;
}


void LogAlarmWid::initFunSLot()
{
    for(int i=0; i<BUS_NUM; ++i) getTableName(i);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁用编辑功能

    model = new SqlTableModel(ui->tableView);
    ui->tableView->setModel(model->model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleSlot(QModelIndex)));

    initBtnBar();
    initTableSlot(0);
}

void LogAlarmWid::initBtnBar()
{
    mBtnBar = new LogBtnBar(ui->widget);
    connect(mBtnBar, SIGNAL(busNumSig(int)), this, SLOT(initTableSlot(int)));
    connect(mBtnBar,SIGNAL(querySig(QString)),model,SLOT(queryFilter(QString)));
    connect(mBtnBar,SIGNAL(clearSig()),this,SLOT(clearTableSlot()));
    connect(mBtnBar,SIGNAL(refreshSig()),this,SLOT(refreshSlot()));
    connect(mBtnBar,SIGNAL(exportSig(int)),this,SLOT(exportSlot(int)));
    connect(mBtnBar,SIGNAL(exportSig(QString, QString)),this,SLOT(exportSlot(QString, QString)));
}

QString LogAlarmWid::getTableName(int id)
{
    return db_alarm_obj(id)->tableName();
}

void LogAlarmWid::initTableSlot(int id)
{
    mid = id;
    m_table = getTableName(id);
    this->refreshTable(m_table);

    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("插接箱")<< tr("回路1") << tr("回路2") << tr("回路3") << tr("合计");
    model->setHeaders(mHeadList);
}


bool LogAlarmWid::refreshTable(const QString &table)
{
    bool ret = model->refreshTable(table);
    if(ret) {
        m_table = table;
        ui->tableView->sortByColumn(0, Qt::DescendingOrder); // 降序排列
        ui->tableView->setColumnHidden(0, true);
    }
    return  ret;
}

void LogAlarmWid::clearTableSlot()
{
    if(model->removeRow(0))
        QTimer::singleShot(100,this,SLOT(clearTableSlot()));
}

void LogAlarmWid::refreshSlot()
{
    initTableSlot(mid);
}

void LogAlarmWid::doubleSlot(QModelIndex)
{
    QString str = tr("是否删除这条纪录?");
    QuMsgBox box(this, str);
    bool ret = box.Exec();
    if(ret)
    {
        int curRow = ui->tableView->currentIndex().row();
        model->removeRow(curRow);
    }
}



/**
 * @brief 按时间段导出
 */
void LogAlarmWid::exportSlot(QString startDate, QString endDate)
{
    qDebug() << startDate << endDate;
}


/**
 * @brief 纪录导出 1日报表 ，2月报表  3 年报表
 */
void LogAlarmWid::exportSlot(int mode)
{
    qDebug() << mode;
}
