#ifndef INITSHM_H
#define INITSHM_H

#include <QObject>
#include "common.h"

class InitShm : public QThread
{
    Q_OBJECT
public:
    explicit InitShm(QObject *parent = 0);

signals:

protected:
    void run();
    void initBoxNum();

    void initThresholdUnit(int bus, int type, int num, sDataUnit &unit, int max);
    void initBoxThreshold();
    void initBusThreshold();
    void initThreshold();

private:
    sDataPacket *shm;
};

#endif // INITSHM_H
