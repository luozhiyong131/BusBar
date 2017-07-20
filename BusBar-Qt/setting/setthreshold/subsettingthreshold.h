#ifndef SUBSETTINGTHRESHOLD_H
#define SUBSETTINGTHRESHOLD_H

#include <QDialog>
#include "common.h"
#include "setshm.h"

typedef struct
{
    int digCur[4][4];
}digData;

namespace Ui {
class SubSettingThreshold;
}

class SubSettingThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit SubSettingThreshold(int bus ,int row ,QWidget *parent = 0);
    ~SubSettingThreshold();

private slots:
    void on_pushButton_clicked();

private:
    void initWid();
    void saveData();
    void setDbItem(DbThresholdItem &item,digData *data,int index);
    void getDigData();

private:
    Ui::SubSettingThreshold *ui;
    int mIndex;
    int mBus;
    SetShm *mShm;
    digData mDigData;
    sDataPacket *mPacket;
};

#endif // SUBSETTINGTHRESHOLD_H
