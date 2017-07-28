#ifndef BOXTOTALWID_H
#define BOXTOTALWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class BoxTotalWid;
}

class BoxTotalWid : public QWidget
{
    Q_OBJECT

public:
    explicit BoxTotalWid(QWidget *parent = 0);
    ~BoxTotalWid();

    void initFun(int bus, int box);

protected:
    void updateData();

protected slots:
    void timeoutDone();

private:
    Ui::BoxTotalWid *ui;
    sTgObjData *mTgBox;
    sEnvData *mEnvBox;
    QTimer *timer;
};

#endif // BOXTOTALWID_H
