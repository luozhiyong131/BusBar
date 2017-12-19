#include "network.h"
#include "send/netsendthread.h"

char currentBus = '0';

void set_hb_IP(const QStringList &ips);

NetWork::NetWork(QObject *parent) : QObject(parent)
{

    QStringList ips;
    ips << "192.168.1.169";
  // set_hb_IP(ips); // 设置目标IP ，也就是把心跳1包发给住

//    mNetDataAnalyze = new NetDataAnalyze(this); // 接收IP 模块数据

    NetSendThread::bulid()->start(); //平板端连接
}

/*
 * SetShm * mShm;
 *  DbNameItem item;
    item.bus = mIndex;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    QString name = ui->lineEdit->text();
    if( (!name.isEmpty()) && (!(name.size() > NAME_LEN))) {
        item.name = name;
        mShm->setName(item);
 *
 * QString rateCurStr = ui->lineEdit_2->text();
    if((!rateCurStr.isEmpty()) && (cm_isDigitStr(rateCurStr)))
    {
        mShm->setLineRatedCur(mIndex,rateCurStr.toInt() * COM_RATE_CUR);
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查电流输入格式！"));
        saveSuccess = false;
    }

    QString boxNumStr = ui->lineEdit_3->text();
    if((!boxNumStr.isEmpty()) && (cm_isDigitStr(boxNumStr)))
    {
        mShm->setLineBoxNum(mIndex,boxNumStr.toInt());
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查插接箱数量输入格式！"));
        saveSuccess = false;
    }
 * */
