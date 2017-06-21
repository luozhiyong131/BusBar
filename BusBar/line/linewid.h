#ifndef LINEWID_H
#define LINEWID_H

#include <QWidget>

namespace Ui {
class LineWid;
}

class LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit LineWid(QWidget *parent = 0);
    ~LineWid();

private:
    Ui::LineWid *ui;
};

#endif // LINEWID_H
