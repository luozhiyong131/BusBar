#ifndef IPSETTINGDLG_H
#define IPSETTINGDLG_H

#include <QWidget>
#include "common.h"
#include "net/udp/sent/udpheartbeat.h"
#define IP1 "192.168.1.163"

namespace Ui {
class IpSettingDlg;
}

class IpSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit IpSettingDlg(QWidget *parent = 0);
    ~IpSettingDlg();

protected:
    void initData();
    void saveData();
    bool ipCheck();

private slots:
    void on_saveBtn_clicked();

private:
    Ui::IpSettingDlg *ui;
    QString mIP1;
    QString mIP2;
    QString mIP3;
    QString mIP4;
    QStringList mIPTotal;
};
int getByIp(const QString &ip);
#endif // IPSETTINGDLG_H
