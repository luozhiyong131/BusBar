#ifndef LOGSWID_H
#define LOGSWID_H

#include <QWidget>

namespace Ui {
class LogsWid;
}

class LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogsWid(QWidget *parent = 0);
    ~LogsWid();

private:
    Ui::LogsWid *ui;
};

#endif // LOGSWID_H
