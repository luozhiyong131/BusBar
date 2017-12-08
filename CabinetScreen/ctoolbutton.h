#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include <QObject>
#include <QToolButton>
#include <QTimer>

class CToolButton : public QToolButton
{
    Q_OBJECT
public:
    CToolButton(QWidget *parent = 0);
    ~CToolButton();

signals:
    void longPressSig(int);

private slots:
    void onPressedSlot();
    void onReleasedSlot();
    void onTimerOut();

private:
    QTimer *timer;
    int  mAccumulator; //累加器
};

#endif // CTOOLBUTTON_H
