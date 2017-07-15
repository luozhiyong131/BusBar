#ifndef BOXDLG_H
#define BOXDLG_H

#include <QDialog>
#include "boxloopwid.h"
#include "boxtotalwid.h"

namespace Ui {
class BoxDlg;
}

class BoxDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BoxDlg(QWidget *parent = 0);
    ~BoxDlg();

    void initBox(int bus, int box);
protected:
    void initWid(int bus, int box);

private:
    Ui::BoxDlg *ui;
    BoxTotalWid *mTotalWid;
    BoxLoopWid *mLine[3];
    sBoxData *mData;
};

#endif // BOXDLG_H
