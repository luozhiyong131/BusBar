#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    frmInput::Instance()->Init("control", "black", 10, 10);
//    frmInput::Instance()->hide();

    MainWindow w;
    w.show();

    return a.exec();
}
