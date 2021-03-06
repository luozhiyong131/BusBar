#ifndef SETLOOPWID_H
#define SETLOOPWID_H

#include "comtablewid.h"
#include "../setline/setlinewid.h"

class SetLoopWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SetLoopWid(QWidget *parent = nullptr);

    void setBus(int bus) {mBus=bus;}

protected slots:
    void timeoutDone();
    void itemClicked(QTableWidgetItem* it);

protected:
    void initWid();
    void checkBus(int index);
    int updateDev(sDataPacket *dev, int row);
    void updateData();

private:
    int mDc, mBus;
    sDevPackets *mPackets ;
};

#endif // SETLOOPWID_H
