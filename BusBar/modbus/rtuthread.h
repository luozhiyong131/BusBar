#ifndef RTUTHREAD_H
#define RTUTHREAD_H

#include <QThread>

#define RTU_BUF_SIZE 512

class RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit RtuThread(QObject *parent = 0);
    
signals:
    
public slots:
    
protected:

private:
    uchar *mBuf;
};

#endif // RTUTHREAD_H
