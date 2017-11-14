#ifndef DPTGTHREAD_H
#define DPTGTHREAD_H

#include <QObject>
#include "common.h"

class DpTgThread : public QThread
{
    Q_OBJECT
public:
    explicit DpTgThread(QObject *parent = 0);
    ~DpTgThread();

signals:

protected:
    void run();

    int averData(int *data, int len=LINE_NUM);
    void tgObj(sObjData *obj, sTgObjData *tg);

    void tgDev(sDevData *dev);
    void tgPacket(sDataPacket *packet);


protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPTGTHREAD_H
