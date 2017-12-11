#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homemainwid.h"
#include "logmainwid.h"
#include "setmainwid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void updateTime();
    void initWidget();

    void onCShow(int value);
    int  mShow;

protected slots:
    void initFunSLot();
    void timeoutDone();

private slots:
    void on_timeBtn_clicked();
    void on_homeBtn_clicked();
    void on_logsBtn_clicked();
    void on_setBtn_clicked();
    void onLongPressSlot(int time);

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    HomeMainWid *mHomeWid;
    LogMainWid *mLogWid;
    SetMainWid *mSetWid;
};

#endif // MAINWINDOW_H
