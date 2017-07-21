#ifndef SYSTEMSETTINGDLG_H
#define SYSTEMSETTINGDLG_H

#include <QWidget>
#include <cstdlib>
#include <QDateTime>
#include <QDebug>
#include "common.h"
#include "smtp/emailwid.h"

namespace Ui {
class SystemSettingDlg;
}

class SystemSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingDlg(QWidget *parent = 0);
    ~SystemSettingDlg();

private slots:
    void on_pushButton_7_clicked();

private:
    Ui::SystemSettingDlg *ui;
    EmailWid *mEmailWid;
};

#endif // SYSTEMSETTINGDLG_H
