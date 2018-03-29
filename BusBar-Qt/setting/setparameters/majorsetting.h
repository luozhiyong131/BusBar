#ifndef MAJORSETTING_H
#define MAJORSETTING_H

#include <QWidget>
#include <QTableWidgetItem>
#include "common.h"
#include "setthreshold/settingthreshold.h"
#include "setshm.h"
#include <QProgressBar>


namespace Ui {
class MajorSetting;
}

class MajorSetting : public QWidget
{
    Q_OBJECT

public:
    explicit MajorSetting(QWidget *parent = 0);
    ~MajorSetting();

    void updateWidget(int index);


private:
    void initWidget();
    void setProgressbarValue(QProgressBar *bar,sDataUnit  *data ,int index);
    void setProcessBarColor(QProgressBar *bar, QString color);

    void upDataLine2(bool show);
    void upDataLine3(bool show);
    void showSum(int value);

public slots:
    void indexChanged(int index);

private slots:
    void barClicked(bool isCur,int index);
    void on_pushButton_clicked();

private:
    Ui::MajorSetting *ui;

    sDataPacket *mPacket;
    SettingThreshold *mSettingThroldWid;
    int mIndex; //当前主路源标志位
    SetShm * mShm;

};

#endif // MAJORSETTING_H
