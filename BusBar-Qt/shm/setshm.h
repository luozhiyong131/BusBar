#ifndef SETSHM_H
#define SETSHM_H

#include <QObject>
#include <QSettings>
#include "dbthreshold.h"
#include "dbdevname.h"

class SetShm : public QObject
{
    Q_OBJECT
public:
    explicit SetShm(QObject *parent = 0);

    bool saveItem(DbThresholdItem &item); // 单一设置

    void setLoopCurAll(DbThresholdItem &item); // 设置所有回路电流
    void setTempAll(DbThresholdItem &item); // 设置所有温度

    void setLineVolAll(DbThresholdItem &item); // 设置成有主路电压
    void setLineCurAll(DbThresholdItem &item); // 设置成有主路电流

    void setName(DbNameItem &item); // 名称设置
    void setLineRatedCur(int index ,int data); //设置母线额定电流
    void setLineBoxNum(int index,int num); //设置母线插接箱数量

protected:
    void setThresholdUnit(int id, DbThresholdItem &item, sDataUnit &unit);

signals:

public slots:

private:
    sDataPacket *shm;
//    QSettings *mSetting;
};

#endif // SETSHM_H
