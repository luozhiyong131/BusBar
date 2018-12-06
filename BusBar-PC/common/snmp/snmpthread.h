#ifndef SNMP_H
#define SNMP_H

#include <QThread>
#include <QScopedPointer>
#include <QMap>
#include <QtSnmpClient.h>
#include <QtCore>
#include "datapacket.h"
#include "configbase.h"

#define MIB_OID_CLEVER  ".1.3.6.1.4.1.30966"

enum{
    SNMP_INTEGER_TYPE = 0x02,
    SNMP_STRING_TYPE = 0x04,
};

struct sSnmpSetCmd
{
    sSnmpSetCmd() {type=SNMP_STRING_TYPE;}
    QString oid;
    ushort type;
    QByteArray value;
};

Q_DECLARE_METATYPE(sSnmpSetCmd)

class SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit SnmpThread(QObject *parent = nullptr);
    ~SnmpThread();

    qint32 requestValue( const QString& oid) {return m_snmp_client->requestValue(oid);}
    qint32 requestValues( const QStringList& oid_list ) {return m_snmp_client->requestValues(oid_list); }
    qint32 requestSubValues( const QString& oid ) {return m_snmp_client->requestSubValues(oid);}   

    qint32 setValue(const sSnmpSetCmd &cmd);

    void startRun();
    void stopRun();
signals:

protected:
    virtual QStringList getRequestValues(int id) = 0;
    virtual int getRequestSubValues(int id, QStringList &oid) = 0;
    virtual void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)=0;

private:
    void run();
    bool requestValues(int id);
    bool requestSubValues(int id);
    void sentOkCmd();
    void clearCount();
    void setOffLine();
    void setAllOffLine();
    void saveErrCmd();

private slots:
    void setSlot();
    void onResponseReceived( const qint32 request_id,const QtSnmpDataList& );
    void onRequestFailed( const qint32 request_id );
    void makeRequest();

private:
    QMutex *mMutex;
    QString m_address;
    QtSnmpClient *m_snmp_client;
    QStringList mOidSubList;
    QtSnmpDataList mValues;

    bool isRun;
    int mCount;
    QTimer *m_timer, *timer;
    int mOidSubIndex, mId;
    sDataPacket *mDataPacket;

protected:
    sDevPackets *mPackets;
    sConfigItem *mItem;

public:
    QList<sSnmpSetCmd> mSetCmdList;//设置成public，在别的类可以访问    
};

#endif // SNMP_H
