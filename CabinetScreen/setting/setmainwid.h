#ifndef SETMAINWID_H
#define SETMAINWID_H

#include <QWidget>

namespace Ui {
class SetMainWid;
}

class SetMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SetMainWid(QWidget *parent = 0);
    ~SetMainWid();

private:
    Ui::SetMainWid *ui;
};

#endif // SETMAINWID_H
