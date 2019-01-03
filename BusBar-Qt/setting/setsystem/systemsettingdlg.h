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
#include "ipsettingdlg.h"
#include "channelsettingdlg.h"

namespace Ui {
class SystemSettingDlg;
}

class SystemSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingDlg(QWidget *parent = 0);
    ~SystemSettingDlg();

signals:
    void busChangedSig(int);

private:
    Ui::SystemSettingDlg *ui;
    EmailWid *mEmailWid;
    NetSettingDlg *mNetWid;
    OtherSettingDlg *mOtherWid;
    IpSettingDlg* mIpWid;
    ChannelSettingDlg* mChannelWid;
};

#endif // SYSTEMSETTINGDLG_H
