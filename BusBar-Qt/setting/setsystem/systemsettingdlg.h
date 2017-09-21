#ifndef SYSTEMSETTINGDLG_H
#define SYSTEMSETTINGDLG_H

#include <QWidget>
#include <cstdlib>
#include <QDateTime>
#include <QDebug>
#include "common.h"
#include "smtp/emailwid.h"
#include "netsettingdlg.h"
#include "othersettingdlg.h"

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

private:
    Ui::SystemSettingDlg *ui;
    EmailWid *mEmailWid;
    NetSettingDlg *mNetWid;
    OtherSettingDlg *mOtherWid;
};

#endif // SYSTEMSETTINGDLG_H
