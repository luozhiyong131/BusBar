#ifndef NETSENDTHREAD_H
#define NETSENDTHREAD_H

#include <QThread>

class NetSendThread : public QThread
{
    Q_OBJECT
    explicit NetSendThread(QObject *parent = nullptr);
public:
    static NetSendThread *bulid();

protected:
    void run();

signals:

public slots:
};

#endif // NETSENDTHREAD_H
