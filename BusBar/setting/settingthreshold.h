#ifndef SETTINGTHRESHOLD_H
#define SETTINGTHRESHOLD_H

#include <QDialog>
#include <QSpinBox>
#include "common.h"
#include "setshm.h"

namespace Ui {
class SettingThreshold;
}

class SettingThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit SettingThreshold(int bus,bool isCur,int index,QWidget *parent = 0);
    ~SettingThreshold();

private slots:
    void on_pushButton_clicked();

private:
    void initWidget();
    void setSuffex(QString str);
    void saveData();

private:
    Ui::SettingThreshold *ui;

    int mBus;
    bool mIsCur;
    int mIndex;
    SetShm *mShm;


};

#endif // SETTINGTHRESHOLD_H
