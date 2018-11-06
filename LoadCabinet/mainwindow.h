#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "websocket.h"
#include "in_mainwid.h"

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

private slots:
    void initFunSLot();
    void timeoutDone();
    void on_timeBtn_clicked();

    void on_homeBtn_clicked();

    void on_inputBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    IN_MainWid *mInputWid;
     WebSocket *dataRecvWS;
};

#endif // MAINWINDOW_H
