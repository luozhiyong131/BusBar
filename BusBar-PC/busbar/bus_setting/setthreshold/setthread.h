#ifndef SETTHREAD_H
#define SETTHREAD_H

#include "setrtucmd.h"

class SetThread : public QThread
{
    Q_OBJECT
    explicit SetThread(QObject *parent = nullptr);
public:
    ~SetThread();
    static SetThread *bulid(QObject *parent = nullptr);
    void append(sThresholdItem &item) {mItems.append(item);}

protected:
    void run();
    void workDown();

private:
    bool isRun;

    BUS_SetShm *mSetShm;
    SetRtuCmd *mRtuCmd;
    QList<sThresholdItem> mItems;
};

#endif // SETTHREAD_H
