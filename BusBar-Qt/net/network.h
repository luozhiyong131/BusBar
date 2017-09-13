#ifndef NETWORK_H
#define NETWORK_H
#include "analyze/netdataanalyze.h"

class NetWork : public QObject
{
public:
    NetWork(QObject *parent = 0);

private:
    NetDataAnalyze *mNetDataAnalyze;
};

#endif // NETWORK_H
