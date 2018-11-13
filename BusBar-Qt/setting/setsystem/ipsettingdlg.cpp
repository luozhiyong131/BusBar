#include "ipsettingdlg.h"
#include "ui_ipsettingdlg.h"

<<<<<<< HEAD
QMap<int, QString> busIPMap;
=======
QMap<int, QString> gBusIPMap;
>>>>>>> origin/lzy


int getByIp(const QString &ip)
{
    for(int i = 0 ; i < BUS_NUM ; ++i)
    {
<<<<<<< HEAD
        if(busIPMap[i] == ip)
=======
        if(gBusIPMap[i] == ip)
>>>>>>> origin/lzy
            return i;
    }
    return -1;
}

QString getIpByKey(int key)
{
    return gBusIPMap[key];
}

IpSettingDlg::IpSettingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpSettingDlg)
{
    ui->setupUi(this);

    initData();
}

IpSettingDlg::~IpSettingDlg()
{
    delete ui;
}

void IpSettingDlg::initData()
{
    bool ret = sys_configFile_open();
    if(ret)
    {
        QStringList ips;
        QString str = sys_configFile_readStr("IP1");
<<<<<<< HEAD
        mIP1 = str;

        str = sys_configFile_readStr("IP2");
        mIP2 = str;

        str = sys_configFile_readStr("IP3");
        mIP3 = str;

        str = sys_configFile_readStr("IP4");
        mIP4 = str;
=======
        if(!str.isEmpty()) {
            ips << str;
            gBusIPMap.insert(0,str);
            ui->IP1lineEdit->setText(str);
        }

        str = sys_configFile_readStr("IP2");
        if(!str.isEmpty()){
            ips << str;
            gBusIPMap.insert(1,str);
            ui->IP2lineEdit->setText(str);
        }

        str = sys_configFile_readStr("IP3");
        if(!str.isEmpty()){
            ips << str;
            gBusIPMap.insert(2,str);
            ui->IP3lineEdit->setText(str);
        }

        str = sys_configFile_readStr("IP4");
        if(!str.isEmpty()){
            ips << str;
            gBusIPMap.insert(3,str);
            ui->IP3lineEdit->setText(str);
        }
>>>>>>> origin/lzy

        sys_configFile_close();
        if(ips.size()) set_hb_IP(ips);
    }
<<<<<<< HEAD
    else
    {
        mIP1 = IP1;
    }

    ui->IP1lineEdit->setText(mIP1);
    ui->IP2lineEdit->setText(mIP2);
    ui->IP3lineEdit->setText(mIP3);
    ui->IP4lineEdit->setText(mIP4);
    mIPTotal.clear();
    if(!mIP1.isEmpty()) mIPTotal<<mIP1;
    if(!mIP2.isEmpty()) mIPTotal<<mIP2;
    if(!mIP3.isEmpty()) mIPTotal<<mIP3;
    if(!mIP4.isEmpty()) mIPTotal<<mIP4;

    busIPMap.clear();
    if(!mIP1.isEmpty()) busIPMap.insert(0,mIP1);
    if(!mIP2.isEmpty()) busIPMap.insert(1,mIP2);
    if(!mIP3.isEmpty()) busIPMap.insert(2,mIP3);
    if(!mIP4.isEmpty()) busIPMap.insert(3,mIP4);

    set_hb_IP(mIPTotal);
=======
>>>>>>> origin/lzy
}

/**
 * @brief IP地址验证
 * @return
 */
bool IpSettingDlg::ipCheck(int i, QLineEdit * edit)
{
    bool ret = true;
    QString str = edit->text();
    if(!str.isEmpty()) {
        ret = cm_isIPaddress(str);
        if(ret){
            gBusIPMap[i] = str;
        } else {
            CriticalMsgBox box(this, tr("IP%1地址错误!").arg(i+1));
        }
    }
    sys_configFile_writeParam(tr("IP%1").arg(i+1), str);

    return ret;

}


void IpSettingDlg::on_saveBtn_clicked()
{
<<<<<<< HEAD
    bool ret = ipCheck();
    if(ret) {
        mIPTotal.clear();
        saveData();
        if(!mIP1.isEmpty()) mIPTotal<<mIP1;
        if(!mIP2.isEmpty()) mIPTotal<<mIP2;
        if(!mIP3.isEmpty()) mIPTotal<<mIP3;
        if(!mIP4.isEmpty()) mIPTotal<<mIP4;

        if(!mIP1.isEmpty()) busIPMap[0] = mIP1;
        if(!mIP2.isEmpty()) busIPMap[1] = mIP2;
        if(!mIP3.isEmpty()) busIPMap[2] = mIP3;
        if(!mIP4.isEmpty()) busIPMap[3] = mIP4;
        set_hb_IP(mIPTotal);
=======
    QStringList ips;
    QLineEdit *edit[4] = {ui->IP1lineEdit, ui->IP2lineEdit, ui->IP3lineEdit, ui->IP4lineEdit};

    for(int i=0; i<4; ++i) {
         bool ret = ipCheck(i, edit[1]);
         if(ret) ips << edit[1]->text();
>>>>>>> origin/lzy
    }
    set_hb_IP(ips);
}
