#ifndef COMMON_H
#define COMMON_H
#include <QtCore>
#include "msgbox.h"




//const QColor gray(174,225,254);//空设备,原为灰色，现为天蓝色
//const QColor green(97,202,40);//正常
//const QColor orange(255,0,0);//报警，原为橘红，现为红色
//const QColor blue(200,200,200);//离线，原为男色，现为灰色



// 倍率定义
#define COM_RATE_VOL	10.0    // 电压
#define COM_RATE_CUR	10.0    // 电流
#define COM_RATE_POW	1000.0  // 功率
#define COM_RATE_ELE	10.0    // 电能
#define COM_RATE_PF	100.0   // 功率因素
#define COM_RATE_TEM	10.0    // 温度
#define COM_RATE_HUM	10.0    // 湿度


QString cm_pathOfData(const QString& name);
bool cm_isDigitStr(const QString &src);

#endif // COMMON_H
