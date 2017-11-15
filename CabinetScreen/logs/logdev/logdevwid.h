#ifndef LOGDEVWID_H
#define LOGDEVWID_H

#include "logcom/logcomelewid.h"

class LogDevWid : public LogComEleWid
{
    Q_OBJECT
public:
    explicit LogDevWid(QWidget *parent = nullptr);

protected:
    void initTable();
    QString getTableName();

};

#endif // LOGDEVWID_H
