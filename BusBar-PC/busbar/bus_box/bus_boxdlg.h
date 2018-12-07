#ifndef BOXDLG_H
#define BOXDLG_H

#include <QDialog>
#include "bus_boxlinetablewid.h"
#include "common.h"

namespace Ui {
class BUS_BoxDlg;
}

class BUS_BoxDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BUS_BoxDlg(QWidget *parent = 0);
    ~BUS_BoxDlg();

    void initBox(int bus, int box);
protected:
    void initWid(int bus, int box);

private slots:
    void on_pushButton_clicked();

private:
    Ui::BUS_BoxDlg *ui;
    BUS_BoxLineTableWid *mLineWid;
    BUS_BoxLoopTableWid *mLoopWid;
};

#endif // BOXDLG_H
