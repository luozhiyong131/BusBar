#ifndef EXCEL_EXPORTLOGTHREAD_H
#define EXCEL_EXPORTLOGTHREAD_H
#include <QtCore>

struct Excel_ExportStr
{
    QString path; // 导出路径
    QString file; // 导出文件名
    QString db; // 数据库表
    QString start; // 开始时间
    QString end; // 结束时间
    QStringList title; // 标头
};


class Excel_ExportLogThread : public QThread
{
public:
    Excel_ExportLogThread(QObject *parent = 0);
    ~Excel_ExportLogThread();

    void set(Excel_ExportStr &ex);
    int getProgress();

protected:
    void run();
    void init();
    virtual void readSql(QList<QStringList> &list);
    void exportExcel(QList<QStringList> &list);

protected:
    Excel_ExportStr mEx;
    int mSize, mAllSize;
    QList<QStringList> mList;
};

#endif // EXCEL_EXPORTLOGTHREAD_H
