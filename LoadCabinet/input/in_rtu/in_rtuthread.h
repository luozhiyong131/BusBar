#ifndef IN_RTUTHREAD_H
#define IN_RTUTHREAD_H

#include "rtucom/rtuthread.h"
#include "in_rtutrans.h"

class IN_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit IN_RtuThread(QObject *parent = nullptr);
public:
    static IN_RtuThread *bulid(QObject *parent = nullptr);
    void sentCmd(sRtuSentCom &cmd);

protected:
    void workDown();
    void sentCmdList();

protected slots:
    void initSlot();

private:
    IN_RtuTrans *mRtu;
    SerialTrans *mSerial;
    QList<sRtuSentCom> mCmdList;
};

#endif // IN_RTUTHREAD_H
