#ifndef SETTINGWID_H
#define SETTINGWID_H

#include <QWidget>
#include "majorsetting.h"

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

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::SettingWid *ui;
    MajorSetting *majorSettingWidget;
};

#endif // SETTINGWID_H
