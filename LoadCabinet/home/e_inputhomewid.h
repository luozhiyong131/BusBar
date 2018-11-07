#ifndef E_INPUTHOMEWID_H
#define E_INPUTHOMEWID_H

#include "e_inputunitwid.h"

namespace Ui {
class E_InputHomeWid;
}

class E_InputHomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit E_InputHomeWid(QWidget *parent = 0);
    ~E_InputHomeWid();

protected:
    void initWid();

private:
    Ui::E_InputHomeWid *ui;

};

#endif // E_INPUTHOMEWID_H
