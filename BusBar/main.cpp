#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{    
    get_share_mem(); // 创建共享内存
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
