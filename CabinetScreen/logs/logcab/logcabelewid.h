#ifndef LOGCABELEWID_H
#define LOGCABELEWID_H

#include "logcom/logcomelewid.h"

class LogCabEleWid : public LogComEleWid
{
    Q_OBJECT
public:
    explicit LogCabEleWid(QWidget *parent = nullptr);

protected:
    void initTable();
    QString getTableName();

protected slots:
    virtual void clearTableSlot();
};

#endif // LOGCABELEWID_H
