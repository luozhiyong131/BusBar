#include "ipsettingdlg.h"
#include "ui_ipsettingdlg.h"

QMap<int, QString> busIPMap;


int getByIp(const QString &ip)
{
    for(int i = 0 ; i < BUS_NUM ; ++i)
    {
        if(busIPMap[i] == ip)
            return i;
    }
    return -1;
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
        QString str = sys_configFile_readStr("IP1");
        mIP1 = str;

        str = sys_configFile_readStr("IP2");
        mIP2 = str;

        str = sys_configFile_readStr("IP3");
        mIP3 = str;

        str = sys_configFile_readStr("IP4");
        mIP4 = str;

        sys_configFile_close();
    }
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
}

/**
 * @brief IP地址验证
 * @return
 */
bool IpSettingDlg::ipCheck()
{
    QString str = ui->IP1lineEdit->text();
    bool ret1 = cm_isIPaddress(str);
    if(ret1 == false)
        CriticalMsgBox box(this, "IP1地址错误!");

    str = ui->IP2lineEdit->text();
    bool ret2 = cm_isIPaddress(str);
    if(ret2 == false)
        CriticalMsgBox box(this, "IP2地址错误!");

    str = ui->IP3lineEdit->text();
    bool ret3 = cm_isIPaddress(str);
    if(ret3 == false)
        CriticalMsgBox box(this, "IP3地址错误!");

    str = ui->IP2lineEdit->text();
    bool ret4 = cm_isIPaddress(str);
    if(ret4 == false)
        CriticalMsgBox box(this, "IP4地址错误!");

    return ret1 && ret2 && ret3 && ret4;
}

/**
 * @brief 保存数据
 */
void IpSettingDlg::saveData()
{
    mIP1 = ui->IP1lineEdit->text();
    sys_configFile_writeParam("IP1", mIP1);

    mIP2 = ui->IP2lineEdit->text();
    sys_configFile_writeParam("IP2", mIP2);

    mIP3 = ui->IP3lineEdit->text();
    sys_configFile_writeParam("IP3", mIP3);

    mIP4 = ui->IP4lineEdit->text();
    sys_configFile_writeParam("IP4", mIP4);
}


void IpSettingDlg::on_saveBtn_clicked()
{
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
    }
}
