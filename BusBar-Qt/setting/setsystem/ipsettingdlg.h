#ifndef IPSETTINGDLG_H
#define IPSETTINGDLG_H

#include <QWidget>
#include "common.h"
#include "net/udp/sent/udpheartbeat.h"
#define IP1 "192.168.1.163"
#define IP2 "192.168.1.164"
#define IP3 "192.168.1.165"
#define IP4 "192.168.1.166"

namespace Ui {
class IpSettingDlg;
}

class IpSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit IpSettingDlg(QWidget *parent = 0);
    ~IpSettingDlg();
    void initData();
    bool ipCheck(int i, QLineEdit *edit);

private slots:
    void on_saveBtn_clicked();

private:
    Ui::IpSettingDlg *ui;
};
int getByIp(const QString &ip);
#endif // IPSETTINGDLG_H
