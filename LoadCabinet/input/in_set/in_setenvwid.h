#ifndef IN_SETENVWID_H
#define IN_SETENVWID_H

#include <QWidget>

namespace Ui {
class IN_SetEnvWid;
}

class IN_SetEnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit IN_SetEnvWid(QWidget *parent = 0);
    ~IN_SetEnvWid();

protected:
    void initWidget();
    void sendCmd();

private slots:
    void on_addrBox_currentIndexChanged(int index);
    void on_envBox_currentIndexChanged(int index);
    void on_updateBtn_clicked();
    void on_setBtn_clicked();

private:
    Ui::IN_SetEnvWid *ui;
};

#endif // IN_SETENVWID_H
