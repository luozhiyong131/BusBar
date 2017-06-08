#include "rtuthread.h"

RtuThread::RtuThread(QObject *parent) :
    QThread(parent)
{
     mBuf = (uchar *)malloc(RTU_BUF_SIZE);
}
