#ifndef SETTEMPWID_H
#define SETTEMPWID_H

#include "setlinetem.h"

class SetLoopTemWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SetLoopTemWid(QWidget *parent = nullptr);

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
    int mBus;
    sDevPackets *mPackets ;
};

#endif // SETTEMPWID_H
