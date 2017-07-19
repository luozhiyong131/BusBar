/*
 * common.cpp
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "common.h"
#include <QWidget>
#include <QHeaderView>


/***
  * 获取程序数据目录
  */
QString cm_pathOfData(const QString& name)
{
    QDir dataDir = QDir::home();
    QString dirName = ".Clever";
    if(!dataDir.exists(dirName))
        dataDir.mkdir(dirName);
    dataDir.cd(dirName);
    return dataDir.absoluteFilePath(name);
}

/***
  *判断一个字符串是否为纯数字
  */
bool cm_isDigitStr(const QString &src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s) //不是纯数字
        return false;

    return true;
}

/**
 * @brief 是否为IP地址
 * @param ip
 * @return
 */
bool cm_isIPaddress(const QString& ip)
{
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    if(regExp.exactMatch(ip))
        return true ;

    return false;
}

/***
  * 获取共享内存
  */
sDataPacket *get_share_mem()
{
    static sDataPacket *shm = NULL;
    if(shm == NULL) {
        shm = share_mem_get();
        share_mem_init();
    }

    return shm;
}
