#ifndef APPTHREAD_H
#define APPTHREAD_H

#include <QtCore>

class AppThread : public QThread
{
    Q_OBJECT
public:
    explicit AppThread(QObject *parent = nullptr);
    ~AppThread();

protected:
    void run();

signals:

public slots:
};

#endif // APPTHREAD_H
