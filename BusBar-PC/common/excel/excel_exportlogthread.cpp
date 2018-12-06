/*
 * excel_exportlogthread.cpp
 * excel导出线程
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "excel_exportlogthread.h"
#include "qexcel.h"
#include "common.h"
#include "icom.h"

extern void DB_selectTableByTime(QString &name, QString &start, QString &end, QList<QStringList> &list);
Excel_ExportLogThread::Excel_ExportLogThread(QObject *parent): QThread(parent)
{
}

Excel_ExportLogThread::~Excel_ExportLogThread()
{
    wait();
}

/**
 * @brief 百分制来计算
 */
int Excel_ExportLogThread::getProgress()
{
    int ret = 100;

    if(mSize < mAllSize)
        ret = (mSize *100.0) / mAllSize ;

    return ret;
}

void Excel_ExportLogThread::set(Excel_ExportStr &ex)
{
    mEx = ex;
    start();
}

/**
 * @brief 读取数据库
 */
void Excel_ExportLogThread::readSql(QList<QStringList> &list)
{
    DB_selectTableByTime(mEx.db, mEx.start, mEx.end, list);
}

/**
 * @brief 数据生成Excel
 */
void Excel_ExportLogThread::exportExcel(QList<QStringList> &list)
{

#if 1
    // 增加头文件 #include <sapi.h>
    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);
        CriticalMsgBox box(0, tr("Qt:初始化Ole失败"));
        return;
    }
#endif

    QString fileName = mEx.path + mEx.file +".xlsx";
#if defined(Q_OS_WIN32)
//    Icom com;
    QExcel excel(this);
    bool ret = excel.createNewExcel(fileName);
    if(ret) {
        excel.selectSheet("Sheet1"); //  Sheet1
        excel.saveAs();

        list.insert(0, mEx.title); // 插入标头
        for(int i=0; i<list.size(); ++i)
        {
            for(int j=1; j<list.at(i).size(); ++j) {
                excel.setCellString(i+1, j, list.at(i).at(j));
            }
            mSize++;
            msleep(25);
        }
        excel.save();
    }
    #elif defined(Q_OS_LINUX)

#endif
}

void Excel_ExportLogThread::init()
{
    mList.clear();
    mSize = mAllSize = 0;
}

void Excel_ExportLogThread::run()
{
    init();
    readSql(mList);

    mAllSize = mList.size();
    exportExcel(mList);
}
