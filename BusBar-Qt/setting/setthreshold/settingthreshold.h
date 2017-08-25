#ifndef SETTINGTHRESHOLD_H
#define SETTINGTHRESHOLD_H

#include <QDialog>
#include <QSpinBox>
#include "common.h"
#include "setshm.h"
#include "frmnum.h"

namespace Ui {
class SettingThreshold;
}

class SettingThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit SettingThreshold(int bus,bool isCur,int index,QWidget *parent = 0);
    explicit SettingThreshold(QWidget *parent = 0);
    ~SettingThreshold();

    void initWidget(int index ,int boxNUm ,int lineNum,int temNum = 0);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_cancel_clicked();

private:
    void initWidget();
    void initData(sDataUnit *unit, int index, int rate);
    void saveData();
    void saveLoopData();
    void setSuffex(QString str);



private:
    Ui::SettingThreshold *ui;

    int mBus;
    int mIndex;
    bool mIsCur;
    SetShm *mShm;

    int mBusNum;
    int mBoxNum;
    int mLineNum;
    int mTemNum;
    bool isBox;


};

#endif // SETTINGTHRESHOLD_H
