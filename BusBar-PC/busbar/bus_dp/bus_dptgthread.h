#ifndef DPTGTHREAD_H
#define DPTGTHREAD_H

#include "bus_dpeleslavethread.h"

class BUS_DpTgThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpTgThread(QObject *parent = 0);
    ~BUS_DpTgThread();

signals:

protected:
    void run();

    int averData(int *data, int len=LOOP_NUM);
    void initData(sObjData *tg);
    void lineTgObj(sDevData &dev);
    void dcLineTgObj(sDevData &dev, int line, int len);

    void tgObj(sDevData &dev);

    void tgBox(sDataPacket *box);
    void tgBus(sDevPackets *bus);


protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
};

#endif // DPTGTHREAD_H
