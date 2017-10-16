#ifndef STARTBOXWID_H
#define STARTBOXWID_H

#include <QWidget>
#include "setthreshold/settingthreshold.h"

namespace Ui {
class startBoxWid;
}

class startBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit startBoxWid(QWidget *parent = 0);
    ~startBoxWid();

    void indexChanged(int index);

private slots:
    void on_tem_btn_1_clicked();

    void on_tem_btn_2_clicked();

    void on_tem_btn_3_clicked();

//    void indexChanged(int index);

private:
    Ui::startBoxWid *ui;
    SettingThreshold *settingWid;
    sDataUnit  *startBoxTem;
    int mIndex;//母线标识符

private:
    void initButtonProPerty();
    void updateWid();
    void switchBtn(int btnIndex);
    int switchProperty(QPushButton *btn);
    void initWid();
};

#endif // STARTBOXWID_H
