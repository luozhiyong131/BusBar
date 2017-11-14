#ifndef LOGCOMELEWID_H
#define LOGCOMELEWID_H

#include <QWidget>
#include "logbtnbar.h"
#include "sqltablemodel.h"

namespace Ui {
class LogComEleWid;
}

class LogComEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogComEleWid(QWidget *parent = 0);
    ~LogComEleWid();

protected:
    void initBtnBar();
    virtual QString getTableName()=0;
    virtual void initTable()=0;
    bool refreshTable(const QString &table);

protected slots:
    void initFunSLot();
    void doubleSlot(QModelIndex);
    void clearTableSlot();
    void refreshSlot();

protected:
    Ui::LogComEleWid *ui;

    LogBtnBar *mBtnBar;
    SqlTableModel *model;
};

#endif // LOGCOMELEWID_H
