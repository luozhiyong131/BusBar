#ifndef IN_SETMAINWID_H
#define IN_SETMAINWID_H

#include "in_setenvwid.h"
#include "in_setthresholdwid.h"

namespace Ui {
class IN_setMainWid;
}

class IN_setMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit IN_setMainWid(QWidget *parent = 0);
    ~IN_setMainWid();

private:
    Ui::IN_setMainWid *ui;
    IN_SetEnvWid *mSetEnvWid;
    IN_SetThresholdWid *mSetThresholdWid;
};

#endif // IN_SETMAINWID_H
