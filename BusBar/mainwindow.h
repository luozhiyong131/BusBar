#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "initshm.h"



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
    void initSerial();

protected slots:
    void initFunSLot();

private:
    Ui::MainWindow *ui;
    InitShm *mInitShm;

};

#endif // MAINWINDOW_H
