#ifndef SETTINGWID_H
#define SETTINGWID_H

#include <QWidget>
#include "majorsetting.h"
#include "subseeting.h"
#include "setsystem/systemsettingdlg.h"
#include "setsystem/checkpassworddlg.h"
#include "temsettingwid.h"

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

//    void dialogClosed(bool ret);

    void on_pushButton_tem_clicked();

private:
    Ui::SettingWid *ui;
    MajorSetting *majorSettingWidget;
    SubSeeting *mSubsettingWid;
    TemSettingWid *mTemWid;
    SystemSettingDlg *mSystemDlg;
//     CheckPasswordDlg *mCheckDlg;
};

#endif // SETTINGWID_H
