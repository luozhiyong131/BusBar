#ifndef STARTBOXWID_H
#define STARTBOXWID_H

#include <QWidget>

namespace Ui {
class startBoxWid;
}

class startBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit startBoxWid(QWidget *parent = 0);
    ~startBoxWid();

private:
    Ui::startBoxWid *ui;
};

#endif // STARTBOXWID_H
