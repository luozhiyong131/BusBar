#ifndef BRANCHWID_H
#define BRANCHWID_H

#include <QWidget>

namespace Ui {
class BranchWid;
}

class BranchWid : public QWidget
{
    Q_OBJECT

public:
    explicit BranchWid(QWidget *parent = 0);
    ~BranchWid();

private:
    Ui::BranchWid *ui;
};

#endif // BRANCHWID_H
