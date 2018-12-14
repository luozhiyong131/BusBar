#ifndef SYSTEMSETTINGDLG_H
#define SYSTEMSETTINGDLG_H


#include "ipsettingdlg.h"

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
    IpSettingDlg* mIpWid;
};

#endif // SYSTEMSETTINGDLG_H
