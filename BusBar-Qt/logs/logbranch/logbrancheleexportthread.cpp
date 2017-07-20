/*
 * logbrancheleexportthread.cpp
 *
 *  Created on: 2017年10月11日
 *      Author: Lzy
 */
#include "logbrancheleexportthread.h"

LogBranchEleExportThread::LogBranchEleExportThread(QObject *parent) : QThread(parent)
{
    mExcelStr = gExcelExportStr;
}

LogBranchEleExportThread::~LogBranchEleExportThread()
{
    wait();
}


void LogBranchEleExportThread::initData(int busId)
{
    mEle = db_branchEle_obj(busId);
    mList.clear();
    start();
}

bool LogBranchEleExportThread::readDb()
{
    bool ret = true;
    QString msg = tr("正在读取数据，请耐心等待!");
    emit readDbSig(msg);

    QStringList heads;
    heads << "No." << "Date" << "Time" << "i-Box" << "Loop 1(kWh)" << "Loop 2(kWh)" << "Loop 3(kWh)" << "Loop(kWh)";
    mList << heads;

    QVector<DbBranchEleItem> items = mEle->selectByDate(mExcelStr->start, mExcelStr->end);
    if(items.size() > 0)
    {
        for(int i=0; i<items.size(); ++i) {
            QStringList str;
            str << QString::number(i+1);
            str << items.at(i).date;
            str << items.at(i).time;
            str << items.at(i).name;
            str << QString::number(items.at(i).loop_1);
            str << QString::number(items.at(i).loop_2);
            str << QString::number(items.at(i).loop_3);
            str << QString::number(items.at(i).loop);
            mList << str;

            if(i%15 == 0) {
                msg = tr("正在解析第%1条数据，请耐心等待!").arg(i+1);
                emit readDbSig(msg);
                msleep(10);
            }
        }
        msg = tr("数据读取完成!!");
    } else {
        ret = false;
        msg = tr("没有纪录数据，无法导出!!");
    }
    emit readDbSig(msg);

    return ret;
}

void LogBranchEleExportThread::run()
{
    bool ret = readDb();
    emit exportSig(ret);
}
