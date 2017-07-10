#ifndef SETTINGTHRESHOLD_H
#define SETTINGTHRESHOLD_H

#include <QDialog>
#include "common.h"

namespace Ui {
class SettingThreshold;
}

class SettingThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit SettingThreshold(sObjData *data,bool isCur,int index,QWidget *parent = 0);
    ~SettingThreshold();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingThreshold *ui;
    sObjData *mData;
    bool mIsCur;
    int mIndex;

private:
    void initWidget();
};

#endif // SETTINGTHRESHOLD_H
