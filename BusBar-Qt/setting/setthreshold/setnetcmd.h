#ifndef SETNETCMD_H
#define SETNETCMD_H

#include "setrtucmd.h"
#include "network.h"

class SetNetCmd : public QObject
{
    Q_OBJECT
public:
    explicit SetNetCmd(QObject *parent = nullptr);

    bool send(sThresholdItem &item);
protected:
    uchar *getData(sThresholdItem &item, int rate);
    bool sentNetData(int bus, uchar *buf, int len);
    bool sentNetDatas(int bus, uchar *buf, int len);

private:
    UdpSentSocket *mSocket;
};

#endif // SETNETCMD_H
