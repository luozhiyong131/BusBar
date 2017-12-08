/*
 * 日志电能纪录基类
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "logcomelewid.h"
#include "ui_logcomelewid.h"

#include <QTableWidgetItem>
#include <QHeaderView>

LogComEleWid::LogComEleWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogComEleWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

LogComEleWid::~LogComEleWid()
{
    delete ui;
}


void LogComEleWid::initFunSLot()
{
    getTableName();

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁用编辑功能

    model = new SqlTableModel(ui->tableView);
    ui->tableView->setModel(model->model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleSlot(QModelIndex)));

    initBtnBar();
    initTable();
}

void LogComEleWid::initBtnBar()
{
    mBtnBar = new LogBtnBar(ui->widget);
    connect(mBtnBar,SIGNAL(querySig(QString)),model,SLOT(queryFilter(QString)));
    connect(mBtnBar,SIGNAL(clearSig()),this,SLOT(clearTableSlot()));
    connect(mBtnBar,SIGNAL(refreshSig()),this,SLOT(refreshSlot()));
}



bool LogComEleWid::refreshTable(const QString &table)
{
    bool ret = model->refreshTable(table);
    if(ret) {
        ui->tableView->resizeColumnsToContents();
        ui->tableView->sortByColumn(0, Qt::DescendingOrder); // 降序排列
        ui->tableView->setColumnHidden(0, true);
    }
    return  ret;
}


void LogComEleWid::refreshSlot()
{
    initTable();
}

void LogComEleWid::doubleSlot(QModelIndex)
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
