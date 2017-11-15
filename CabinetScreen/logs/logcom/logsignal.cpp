/*
 * 日志信息信号类
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "logsignal.h"

LogSignal::LogSignal(QObject *parent) : QObject(parent)
{

}

LogSignal *LogSignal::get()
{
    static LogSignal *sington = new LogSignal();
    return sington;
}

void LogSignal::changeType(int type)
{
    emit logTypeSig(type);
}
