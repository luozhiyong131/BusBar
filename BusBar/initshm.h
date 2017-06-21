#ifndef INITSHM_H
#define INITSHM_H

#include <QObject>
#include "common.h"

class InitShm : public QObject
{
    Q_OBJECT
public:
    explicit InitShm(QObject *parent = 0);

signals:

protected:
    void initBoxNum();

private:
    sDataPacket *shm;
};

#endif // INITSHM_H
