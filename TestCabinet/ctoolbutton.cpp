#include "ctoolbutton.h"

CToolButton::CToolButton(QWidget *parent): QToolButton(parent)
{
    mAccumulator = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(this, SIGNAL(pressed()), this, SLOT(onPressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(onReleasedSlot()));

}

CToolButton::~CToolButton()
{
   // delete timer;
}

void CToolButton::onPressedSlot()
{
    timer->start(100);
}

void CToolButton::onReleasedSlot()
{
    timer->stop();
    emit longPressSig(mAccumulator);
    mAccumulator = 0;
}

void CToolButton::onTimerOut()
{
    mAccumulator += 100;
}
