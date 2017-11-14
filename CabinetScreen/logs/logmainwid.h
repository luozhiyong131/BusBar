#ifndef LOGMAINWID_H
#define LOGMAINWID_H

#include <QWidget>

namespace Ui {
class LogMainWid;
}

class LogMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogMainWid(QWidget *parent = 0);
    ~LogMainWid();

private:
    Ui::LogMainWid *ui;
};

#endif // LOGMAINWID_H
