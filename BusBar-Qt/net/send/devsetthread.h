#ifndef DEVSETTHREAD_H
#define DEVSETTHREAD_H

#include <QObject>
#include <QMap>
#include <QThread>

#include "netdataformat.h"
#include "shm/setshm.h"
/**
 * 在网络中传输 数据库包
 */
typedef struct
{
    uchar num;
    uchar addr;	/*地址*/
    QByteArray fn;	/*功能码*/
    //ushort len; /*数据长度*/
    QByteArray data; /*数据*/
}dev_data;


static  QMap<uchar ,QMap<QByteArray ,dev_data>> gDevMap;


class DevSetThread : public QThread
{
    Q_OBJECT
public:
    explicit DevSetThread(QObject *parent = nullptr);

    static DevSetThread* bulid();

    void insert(const dev_data_packet &pkt);

protected:
    void run();
    int devToItem(dev_data &cData, DbThresholdItem &item); //设置 -- 本地共享内存 or 远端
    bool saveLocal(DbThresholdItem &item);  // 本地设置
    bool saveFarend(DbThresholdItem &item); // 远端设置
    void setNameNum(dev_data &cData); // 设置名字什么的

public:
    bool isRun;


protected:
    SetShm *mShm; //操作共享内存

signals:

public slots:
};

#endif // DEVSETTHREAD_H
