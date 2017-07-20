#include "mainwindow.h"
#include <QApplication>
#include "frminput.h"
#include "frmnum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

<<<<<<< HEAD
    // qApp->setFont(QFont("Microsoft YaHei", 10));
    //qApp->setFont(QFont("WenQuanYi Micro Hei", 15));

    //在main函数中就加载输入法面板,保证整个应用程序可以使用输入法
    //以下方法打开中文输入法
    frmInput::Instance()->Init("control", "black", 11, 11);
    //以下方法打开数字键盘
    // frmNum::Instance()->Init("lightgray",10);
=======
//    frmInput::Instance()->Init("control", "black", 10, 10);
//    frmInput::Instance()->hide();
>>>>>>> wdl

    MainWindow w;
    w.show();

    return a.exec();
}
