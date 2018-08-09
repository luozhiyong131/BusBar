﻿/*
 * common.cpp
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "common.h"
#include <QWidget>
#include <QHeaderView>
#include <time.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <unistd.h>

void com_setBackColour(const QString &str,QWidget *target)
{
    target->setWindowTitle(str);
    //target->setWindowFlags(Qt::FramelessWindowHint);
    target->setAutoFillBackground(true) ;
    QPalette paletteTool = target->palette() ;
    QBrush brushToolPic(QColor(WIDGET_BACK_COLOR)) ;
    QBrush brushToolwhite(QColor(BUTTON_BACK_COLOR)) ;
    paletteTool.setBrush(QPalette::Window,brushToolPic) ;
    paletteTool.setBrush(QPalette::Base,brushToolPic) ;
    paletteTool.setBrush(QPalette::Button,brushToolwhite) ;
    target->setPalette(paletteTool) ;

    target->setStyleSheet(BTN_FOCUS_BACK_COLOR);
    target->setWindowIcon(QIcon(":/image/logo.jpg")); //
}



/***
  * 获取程序数据目录
  */
QString cm_pathOfData(const QString& name)
{
    QDir dataDir("/root/");// = QDir::home();
    QString dirName = ".LoadCabinet";
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
//sDataPacket *get_share_mem()
//{
//    static sDataPacket *shm = NULL;
//    if(shm == NULL) {
//        shm = share_mem_get();
//        share_mem_init();
//    }

//    return shm;
//}

void set_background_icon(QWidget *widget, const QString &icon)
{
    QPalette palette;
    QPixmap map = QPixmap(icon);
    palette.setBrush(QPalette::Background, QBrush(map));
    widget->setAutoFillBackground(true);
    widget->setPalette(palette);
}

void set_background_color(QWidget *widget, const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(palette);
}


void set_background_icon(QWidget *widget, const QString &icon,const QSize &size)
{    
    QPalette palette; //调色板
    QPixmap map = QPixmap(icon).scaled(size);
    palette.setBrush(QPalette::Background, QBrush(map)); //刷
    widget->setAutoFillBackground(true); //设置自动填充地面
    widget->setPalette(palette);
}




