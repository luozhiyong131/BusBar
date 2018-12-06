#ifndef BUILDJSON_H
#define BUILDJSON_H
#include "datapacket.h"

class BuildJson
{
public:
    BuildJson();

    virtual bool getJson(sDataPacket *packet, QJsonObject &json);
    bool saveJson(const QString &name, QJsonObject &json);

protected:
    virtual void head(sDataPacket *packet,QJsonObject &obj);
    virtual void uutInfo(sDataPacket *packet, QJsonObject &json);
    virtual void ateInfo(sDataPacket *packet, QJsonObject &json);

    void objData(sObjData *ObjData, QJsonObject &obj);
    void lineData(sDevData *ObjData, QJsonObject &json);
    void outputData(sDevData *ObjData, QJsonObject &json);
    void loopData(sDevData *ObjData, QJsonObject &json);

    void thresholdItem(int index, int id, sDataUnit &unit, double rate, QJsonObject &json);
    void lineVolThreshold(sDevData *ObjData, QJsonArray &jsonArray);
    void lineCurThreshold(sDevData *ObjData, QJsonArray &jsonArray);
    void loopCurThreshold(sDevData *ObjData, QJsonArray &jsonArray);
    void outputCurThreshold(sDevData *ObjData, QJsonArray &jsonArray);
    void envThreshold(sDevData *ObjData, QJsonArray &jsonArray);
    void thresholds(sDevData *ObjData, QJsonObject &json);

    void envItem(int index, int id, const QString &name, int status, QJsonObject &json);
    void envSensor(sEnvData *ObjData, QJsonArray &jsonArray);
    void envs(sEnvData *ObjData, QJsonObject &json);

    void alarmItem(int index, int id, sDataUnit &unit, double rate, QJsonArray &jsonArray);
    void alarms(QJsonObject &json);

    void devData(sDataPacket *packet, QJsonObject &obj);

protected:
    QJsonArray mAlarmJsonArray;
};

#endif // BUILDJSON_H
