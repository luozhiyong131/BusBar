#ifndef E_STATUSHOMEWID_H
#define E_STATUSHOMEWID_H

#include "e_inputunitwid.h"

namespace Ui {
class E_statusHomeWid;
}

class E_statusHomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit E_statusHomeWid(QWidget *parent = 0);
    ~E_statusHomeWid();

protected:
    void updateWid();
    bool checkRunTime();
    void updateRunTime();

    void startUp();
    void stopFun();
    void openInput();
    void setMode();

private slots:
    void timeoutDone();

    void on_startBtn_clicked();
    void on_openBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::E_statusHomeWid *ui;
    QTimer *timer;

    int mSec;
    bool isRun;

};

#endif // E_STATUSHOMEWID_H
