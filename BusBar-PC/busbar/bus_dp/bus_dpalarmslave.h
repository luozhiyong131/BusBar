#ifndef DPALARMSLAVE_H
#define DPALARMSLAVE_H

#include <QObject>
#include "bus_com/bus_setshm.h"

class BUS_DpAlarmSlave : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpAlarmSlave(QObject *parent = 0);
    ~BUS_DpAlarmSlave();

signals:

protected:
    void run();
    void unitAlarm(const QString &nameStr, QString &typeStr, QString &msg,
                   sDataUnit &unit, double rate, const QString &sym);

    void boxAlarm(sDataPacket &box);
    void busAlarm(int id);
    void checkAlarm();

   void saveMsg(const QString &typeStr, const QString &str);

protected slots:
    void timeoutDone();

private:
     bool isRun;
     QTimer *timer;
     BUS_DataPackets *shm;
     int mBusId;
     QStringList mAlarmStr;
};

QString get_email_str();
QStringList get_alarm_str();
#endif // DPALARMSLAVE_H
