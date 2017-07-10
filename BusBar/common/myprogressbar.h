#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QProgressBar>

class MyProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit MyProgressBar(QWidget* parent=0);

signals:
    void clicked();
//    void isClicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MYPROGRESSBAR_H
