#ifndef SETTINGTHRESHOLD_H
#define SETTINGTHRESHOLD_H

#include <QDialog>

namespace Ui {
class SettingThreshold;
}

class SettingThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit SettingThreshold(QWidget *parent = 0);
    ~SettingThreshold();

private:
    Ui::SettingThreshold *ui;
};

#endif // SETTINGTHRESHOLD_H
