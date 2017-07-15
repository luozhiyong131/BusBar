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

    int averData(int *data, int len=3);
    void tgObj(sObjData *obj, sTgObjData *tg);

    void tgBox(sBoxData *box);

    void tgBusLine(sBusData *bus);
    void tgBus(sBusData *bus);


protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
     sDataPacket *shm;
};

#endif // DPTGTHREAD_H
