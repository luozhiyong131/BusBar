#ifndef HOMEWID_H
#define HOMEWID_H

#include <QWidget>
#include "smtp/emailwid.h"

namespace Ui {
class HomeWid;
}

class HomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWid(QWidget *parent = 0);
    ~HomeWid();

private:
    Ui::HomeWid *ui;

    EmailWid *mEmailWid;
};

#endif // HOMEWID_H
