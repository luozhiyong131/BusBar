#ifndef OTHERSETTINGDLG_H
#define OTHERSETTINGDLG_H

#include <QWidget>
#include "datetimesettingdlg.h"
#include "passordsettingdlg.h"

namespace Ui {
class OtherSettingDlg;
}

class OtherSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit OtherSettingDlg(QWidget *parent = 0);
    ~OtherSettingDlg();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OtherSettingDlg *ui;
};

#endif // OTHERSETTINGDLG_H
