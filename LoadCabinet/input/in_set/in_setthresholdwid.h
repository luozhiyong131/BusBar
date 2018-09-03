#ifndef IN_SETTHRESHOLDWID_H
#define IN_SETTHRESHOLDWID_H

#include <QWidget>

namespace Ui {
class IN_SetThresholdWid;
}

class IN_SetThresholdWid : public QWidget
{
    Q_OBJECT

public:
    explicit IN_SetThresholdWid(QWidget *parent = 0);
    ~IN_SetThresholdWid();

protected:
    void initWidget();
    void sendCmd();

private slots:
    void on_addrBox_currentIndexChanged(int index);
    void on_lineBox_currentIndexChanged(int index);
    void on_updateBtn_clicked();
    void on_setBtn_clicked();

private:
    Ui::IN_SetThresholdWid *ui;
};

#endif // IN_SETTHRESHOLDWID_H
