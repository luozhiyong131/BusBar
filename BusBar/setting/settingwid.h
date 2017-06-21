#ifndef SETTINGWID_H
#define SETTINGWID_H

#include <QWidget>

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
    Ui::SettingWid *ui;
};

#endif // SETTINGWID_H
