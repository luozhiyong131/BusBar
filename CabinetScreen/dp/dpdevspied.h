#ifndef DPDEVSPIED_H
#define DPDEVSPIED_H

#include "common.h"

class DpDevSpied : public QThread
{
    Q_OBJECT
public:
    explicit DpDevSpied(QObject *parent = nullptr);

protected:
    void run();
    void checkDevState();
    void devOffLine(int id);

signals:

protected slots:
    void timeoutDone();

private:
    bool isRun;
    QTimer *mTimer;
    sDataPacket *shm;
};

#endif // DPDEVSPIED_H
