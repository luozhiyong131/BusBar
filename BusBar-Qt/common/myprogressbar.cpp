#include "myprogressbar.h"

MyProgressBar::MyProgressBar(QWidget* parent):QProgressBar(parent)
{

}

void MyProgressBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
//        emit isClicked();
    }

//    QLabel::mousePressEvent(event);//将该事件传给父类处理
}
