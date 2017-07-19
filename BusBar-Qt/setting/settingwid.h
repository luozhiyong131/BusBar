#ifndef SETTINGWID_H
#define SETTINGWID_H

#include <QWidget>
#include "majorsetting.h"
#include "subseeting.h"
#include "systemsettingdlg.h"

namespace Ui {
class SettingWid;
}

class SettingWid : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWid(QWidget *parent = 0);
    ~SettingWid();

private:
    void initWidget();

public slots:
    void busChangedSlot(int);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SettingWid *ui;
    MajorSetting *majorSettingWidget;
    SubSeeting *mSubsettingWid;
    SystemSettingDlg *mSystemDlg;
};

#endif // SETTINGWID_H
