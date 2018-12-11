#ifndef BRANCHWID_H
#define BRANCHWID_H

#include "bus_branchtablewid.h"

namespace Ui {
class BUS_BranchWid;
}

class BUS_BranchWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_BranchWid(QWidget *parent = 0);
    ~BUS_BranchWid();

signals:
    void busChangedSig(int);

private:
    Ui::BUS_BranchWid *ui;
    BUS_BranchTableWid *mTableWid;
};

#endif // BRANCHWID_H
