#ifndef DEVSETTHREAD_H
#define DEVSETTHREAD_H

#include <QObject>
#include <QList>
#include <QThread>

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


static  QList<dev_data> gDevList;


class DevSetThread : public QThread
{
    Q_OBJECT
public:
    explicit DevSetThread(QObject *parent = nullptr);

    DevSetThread* bulid();

protected:
    void run();

protected:
    bool isRun;
signals:

public slots:
};

#endif // DEVSETTHREAD_H
