/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "snmp_zmrecv.h"

SNMP_ZmRecv::SNMP_ZmRecv( )
{
    mRate =1;
}


void SNMP_ZmRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    getMS(oid);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
    int item = getItemByOid(2);
    switch (item) {
    case 1: devInfo(data); break;
    case 2: lineData(data); break;
    case 3: loopData(data); break;
    case 4: envData(data); break;

    case 5: case 6: case 7:  case 9:
    case 10: outputData(data); break;
    case 8: outputCur(data); break;

    default:  qDebug() << "SNMP_ZmRecv::onResponseReceived" << item; break;
    }

}

void SNMP_ZmRecv::outputData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(2);
    switch (item) {
    case 5:  sprintf(obj->name, "%s", data.data()); break;
    case 6:  obj->delay = data.toDouble() ; break;
    case 7:  obj->sw = data.toStdString()=="OFF"?0:1;break;
    case 9:  obj->pf = data.toDouble()*100 ; break;
    case 10:  obj->ele = data.toDouble()*10 ; break;
     default: qDebug() << "SNMP_ZmRecv::outputData" << item; break;
    }

}

void SNMP_ZmRecv::outputCur(const QByteArray &data)
{
    int id = getItemByOid(4) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(3);
    switch (item) {
    case 1: obj->cur.value = data.toDouble() * 10; break;
    case 2: obj->cur.min = data.toDouble() * 10 ; break;
    case 3: obj->cur.crMin = data.toDouble() * 10; break;
    case 4: obj->cur.crMax = data.toDouble() * 10 ; break;
    case 5: obj->cur.max = data.toDouble() * 10; break;
    default: qDebug() << "SNMP_ZmRecv::outputCur" << item; break;
    }
}

void SNMP_ZmRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    env->envNum = 2;
    int item = getItemByOid(3);
    switch (item) {
    case 1: env->tem[0].value = data.toDouble(); break;
    case 2: env->tem[1].value = data.toDouble(); break;
    case 3: env->hum[0].value = data.toDouble(); break;
    case 4: env->hum[1].value = data.toDouble(); break;

    case 5: env->door[0] = data.toDouble() ; break;
    case 6: env->door[1] = data.toDouble() ; break;
    case 7: env->smoke[0] = data.toDouble() ; break;
    case 8: env->water[0] = data.toDouble() ; break;

    case 9: env->tem[0].min = data.toDouble() ; break;
    case 10: env->tem[0].crMin = data.toDouble(); break;
    case 11: env->tem[0].crMax = data.toDouble() ; break;
    case 12: env->tem[0].max = data.toDouble(); break;

    case 13: env->tem[1].min = data.toDouble() ; break;
    case 14: env->tem[1].crMin = data.toDouble(); break;
    case 15: env->tem[1].crMax = data.toDouble() ; break;
    case 16: env->tem[1].max = data.toDouble(); break;

    case 17: env->hum[0].min = data.toDouble(); break;
    case 18: env->hum[0].crMin = data.toDouble(); break;
    case 19: env->hum[0].crMax = data.toDouble(); break;
    case 20: env->hum[0].max = data.toDouble(); break;

    case 21: env->hum[1].min = data.toDouble(); break;
    case 22: env->hum[1].crMin = data.toDouble(); break;
    case 23: env->hum[1].crMax = data.toDouble(); break;
    case 24: env->hum[1].max = data.toDouble(); break;

    default: qDebug() << "SNMP_ZmRecv::envData" << item; break;
    }
}

void SNMP_ZmRecv::lineData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.line[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->cur.value = data.toDouble() * 10;break;
    case 2: obj->vol.value = data.toDouble() ;
            if(obj->vol.value) obj->sw=1; else obj->sw=0; break;
    case 3: obj->pow = data.toDouble(); break;
    case 4: obj->pf = data.toDouble()*100 ; break;
    case 5: obj->ele = data.toDouble()*10 ; break;

    case 6: obj->cur.min = data.toDouble() * 10 ; break;
    case 7: obj->cur.crMin = data.toDouble() * 10; break;
    case 8: obj->cur.crMax = data.toDouble() * 10 ; break;
    case 9: obj->cur.max = data.toDouble() * 10; break;

    case 10: obj->vol.min = data.toDouble() ; break;
    case 11: obj->vol.crMin = data.toDouble() ; break;
    case 12: obj->vol.crMax = data.toDouble() ; break;
    case 13: obj->vol.max = data.toDouble() ; break;
    default: qDebug() << "SNMP_ZmRecv::lineData" << item; break;
    }

}

void SNMP_ZmRecv::loopData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.loop[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->sw = data.toStdString()=="opened"?0:1; break;
    case 2:                         break;
    case 3: obj->cur.value = data.toDouble()*10; break;
    case 4: obj->vol.value = data.toDouble(); break;
    case 5: obj->ele = data.toDouble()*10 ; break;
    case 6: obj->activePow = data.toDouble();break;

    case 7: obj->cur.min = data.toDouble()*10 ; break;
    case 8: obj->cur.crMin = data.toDouble()*10; break;
    case 9: obj->cur.crMax = data.toDouble()*10 ; break;
    case 10: obj->cur.max = data.toDouble()*10; break;
    default: qDebug() << "SNMP_ZmRecv::loopData" << item; break;
    }
}



void SNMP_ZmRecv::devInfo(const QByteArray &data)
{
    bool ok;
    int item = getItemByOid(3);
    switch (item) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); mDataPacket->txType = 1 ;break;
    case 2: devTypeData(data.toHex().toInt(&ok,16), mDataPacket); break;
    case 3: mDataPacket->data.outputNum = data.toHex().toInt(&ok,16); break;
    case 4: sprintf(mDataPacket->mac, "%s",data.data()); break;
    case 5: sprintf(mDataPacket->versionStr, "%s",data.data()); break;
    case 6: mDataPacket->hz = data.toHex().toInt(&ok,16); break;
    default:
        break;
    }
}

void SNMP_ZmRecv::getMS(const QByteArray &oid)
{
    mOid = QString(oid).remove(MIB_OID_CLEVER).simplified();
    int id = getItemByOid(1);
    if(id >= 0) {
        mDataPacket = &(mPackets->dev[id]);
        mDataPacket->id = id;
        mDataPacket->offLine = 10;
    }
}

int SNMP_ZmRecv::getItemByOid(int id)
{
    QStringList list = mOid.split(".");
    return list.at(id+1).toInt();
}
