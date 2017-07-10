#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QProgressBar>
#include "datapacket.h"

class MyProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit MyProgressBar(QWidget* parent=0);
    void setPacket(sObjData *data,bool isCur,int index);

signals:
    void clicked(sObjData *data,bool isCur,int index);

private :
    sObjData *mData;
    bool mIsCur;
    int mIndex;

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MYPROGRESSBAR_H
