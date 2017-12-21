#ifndef SETBOX_H
#define SETBOX_H

/******************************************************************
 *
 * : 设置在线设备类
 *
********************************************************************/

#include <QThread>
#include "datapacket.h"
#include "rtuthread.h"
#include <QList>
#include "setshm.h"

extern RtuThread *rtu[4];

class SetBOXThread : public QThread
{
    Q_OBJECT
public:
    explicit SetBOXThread(QObject *parent = nullptr);
    static SetBOXThread *bulid();

    // ----- 发送数据接口  ------
    bool send(int runType, DbThresholdItem item);
    bool isRun();
protected:
    void run();
    int transmit(int addr, ushort reg, ushort len, int busID = -1); //发送数据并回收
    int sendData(int addr, ushort reg, ushort len, int busID = -1, bool value = false); //发送数据

    bool saveItem(DbThresholdItem &item); // 单一设置

    void saveAllItem(DbThresholdItem &item); // 统一设置
    void setLoopVolAll(DbThresholdItem &item); // 设置所有回路电压
    void setLoopCurAll(DbThresholdItem &item); // 设置所有回路电流
    void setTempAll(DbThresholdItem &item); // 设置所有接插箱温度

    void setLineVolAll(DbThresholdItem &item); // 设置所有主路电压
    void setLineCurAll(DbThresholdItem &item); // 设置所有主路电流
    void setLineTempAll(DbThresholdItem &item); // 设置所有始端箱温度

signals:

public slots:
    void busChangedSlot(int cBusID);

private:
   int isRunType; // 0 - 空闲  1 - 单元设置  2 - 统一设置
   int mBusID; //当前母线

   //通用
   DbThresholdItem mItem;

};

#endif // SETBOX_H
