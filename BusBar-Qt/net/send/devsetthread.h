#ifndef DEVSETTHREAD_H
#define DEVSETTHREAD_H

#include <QObject>
#include <QMap>
#include <QThread>

#include "netdataformat.h"
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

    DevSetThread* bulid();

    void insert(const dev_data_packet &pkt);

protected:
    void run();

public:
    bool isRun;
signals:

public slots:
};

#endif // DEVSETTHREAD_H
