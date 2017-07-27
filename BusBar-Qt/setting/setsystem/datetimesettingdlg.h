#ifndef DATETIMESETTINGDLG_H
#define DATETIMESETTINGDLG_H

#include <QWidget>
#include "common.h"

namespace Ui {
class DatetimeSettingDlg;
}

class DatetimeSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit DatetimeSettingDlg(QWidget *parent = 0);
    ~DatetimeSettingDlg();

private slots:
    void on_pushButton_7_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    void initDateTime();

private:
    Ui::DatetimeSettingDlg *ui;
};

#endif // DATETIMESETTINGDLG_H
