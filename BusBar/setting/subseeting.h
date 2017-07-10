#ifndef SUBSEETING_H
#define SUBSEETING_H

#include <QWidget>

namespace Ui {
class SubSeeting;
}

class SubSeeting : public QWidget
{
    Q_OBJECT

public:
    explicit SubSeeting(QWidget *parent = 0);
    ~SubSeeting();

private:
    Ui::SubSeeting *ui;
};

#endif // SUBSEETING_H
