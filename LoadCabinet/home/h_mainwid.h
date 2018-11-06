#ifndef H_MAINWID_H
#define H_MAINWID_H

#include "e_statushomewid.h"
#include "e_inputhomewid.h"

namespace Ui {
class H_MainWid;
}

class H_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit H_MainWid(QWidget *parent = 0);
    ~H_MainWid();

private:
    Ui::H_MainWid *ui;
    E_InputHomeWid *mInputWid;
    E_statusHomeWid *mStatusWid;
};

#endif // H_MAINWID_H
