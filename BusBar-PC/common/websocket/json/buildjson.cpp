/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buildjson.h"

BuildJson::BuildJson()
{

}


bool BuildJson::getJson(sDataPacket *packet, QJsonObject &json)
{
    bool ret = true;

    if(packet->offLine > 0) {
        head(packet, json);
        devData(packet, json);
        //  pduNetData(packet->net, json);
    } else {
        ret = false;
    }

    return ret;
}

bool BuildJson::saveJson(const QString &name, QJsonObject &json)
{
    QJsonDocument jsonDoc(json);
    QByteArray ba = jsonDoc.toJson();
    QFile file("F:/" + name+".json");
    bool ret = file.open(QIODevice::WriteOnly);
    if(ret) {
        file.write(ba);
        file.close();
    } else {
        qDebug() << "write json file failed";
    }

    return ret;
}

void BuildJson::head(sDataPacket *packet,QJsonObject &obj)
{
    obj.insert("company", "CLEVER");
    obj.insert("version", 1);

    uutInfo(packet, obj);
    ateInfo(packet, obj);
}

void BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "si_module");

    QString str = "cab " + QString::number(packet->id);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("pdu_ip",  "---");
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "Si-PDU");
    obj.insert("pdu_spec", 1);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "SI-PDU " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}

void BuildJson::objData(sObjData *ObjData, QJsonObject &obj)
{
    int value = ObjData->vol.value ;
    if(value >= 0) obj.insert("vol", value / COM_RATE_VOL);

    value = ObjData->cur.value ;
    if(value >= 0) obj.insert("cur", value / COM_RATE_CUR);

    value = ObjData->pow;
    if(value >= 0) obj.insert("pow", value / COM_RATE_POW);

    value = ObjData->ele;
    if(value >= 0) obj.insert("ele", value / COM_RATE_ELE);

    value = ObjData->pf;
    if(value >= 0) obj.insert("PF", value / COM_RATE_PF);

    value = ObjData->sw;
    if(value >= 0) obj.insert("switch", value);
}

void BuildJson::lineData(sDevData *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    QString modeStr = "line";

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        subObj.insert("id", i);
        subObj.insert("name", modeStr +" "+ QString::number(i+1));

        objData(&(ObjData->line[i]), subObj);
        jsonArray.append(subObj);
    }

    if(num > 0) json.insert(QString("%1_item_list").arg(modeStr), QJsonValue(jsonArray));
}

void BuildJson::outputData(sDevData *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    QString modeStr = "output";

    int num = ObjData->outputNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        subObj.insert("id", i);
        subObj.insert("name", modeStr +" "+ QString::number(i+1));

        objData(&(ObjData->output[i]), subObj);
        jsonArray.append(subObj);
    }

    if(num > 0) json.insert(QString("%1_item_list").arg(modeStr), QJsonValue(jsonArray));
}

void BuildJson::loopData(sDevData *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    QString modeStr = "loop";

    int num = ObjData->loopNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        subObj.insert("id", i);
        subObj.insert("name", modeStr +" "+ QString::number(i+1));

        objData(&(ObjData->loop[i]), subObj);
        jsonArray.append(subObj);
    }

    if(num > 0) json.insert(QString("%1_item_list").arg(modeStr), QJsonValue(jsonArray));
}

void BuildJson::alarmItem(int index, int id, sDataUnit &unit, double rate, QJsonArray &jsonArray)
{
    QString item, symbol, str="L";
    switch (index) {
    case 1:
        item = "相电压告警";
        symbol = "V";
        break;
    case 2:
        item = "相电流告警";
        symbol = "A";
        break;
    case 3:
        item = "输出位电流告警";
        symbol = "A";
        str = "Output";
        break;
    case 4:
        item = "输出位电压告警";
        symbol = "V";
        str = "Output";
        break;
    case 5:
        item = "温度告警";
        symbol = "°C";
        str = "温度";
        break;
    case 6:
        item = "湿度压告警";
        symbol = "%";
        str = "湿度";
        break;
    default:
        break;
    }

    QJsonObject subObj;
    QString contents = str + QString::number(id+1) + ", " +
            "当前值:" + unit.value/rate + symbol + ", " +
            "最小值:" + unit.min/rate + symbol + ", " +
            "最大值:" + unit.max/rate + symbol + "; ";
    subObj.insert("item", item);
    subObj.insert("contents", contents);

    jsonArray.append(subObj);
}

void BuildJson::thresholdItem(int index, int id, sDataUnit &unit, double rate, QJsonObject &json)
{
    json.insert("id",  id);
    json.insert("type_index", index); //

    json.insert("min", unit.min / rate);
    json.insert("max", unit.max / rate);
    json.insert("cr_min", unit.min / rate);
    json.insert("cr_max", unit.max / rate);

    if(unit.alarm == 2) {
        unit.alarm = 3;
        alarmItem(index, id, unit, rate, mAlarmJsonArray);
    }
}

void BuildJson::lineVolThreshold(sDevData *ObjData, QJsonArray &jsonArray)
{
    int index = 1;

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->line[i].vol, COM_RATE_VOL, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::lineCurThreshold(sDevData *ObjData, QJsonArray &jsonArray)
{
    int index = 2;

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->line[i].cur, COM_RATE_CUR, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::outputCurThreshold(sDevData *ObjData, QJsonArray &jsonArray)
{
    int index = 3;

    int num = ObjData->outputNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->output[i].cur, COM_RATE_CUR, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::loopCurThreshold(sDevData *ObjData, QJsonArray &jsonArray)
{
    int index = 4;

    int num = ObjData->loopNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->loop[i].cur, COM_RATE_CUR, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::envThreshold(sDevData *ObjData, QJsonArray &jsonArray)
{
    int index = 5;

    int num = ObjData->env.envNum;
    for(int i=0; i<num; ++i) {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->env.tem[i], COM_RATE_TEM, subObj);
        jsonArray.append(subObj);
    }

    index = 6;
    for(int i=0; i<num; ++i) {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->env.hum[i], COM_RATE_TEM, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::thresholds(sDevData *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;

    lineVolThreshold(ObjData, jsonArray);
    lineCurThreshold(ObjData, jsonArray);
    outputCurThreshold(ObjData, jsonArray);
    loopCurThreshold(ObjData, jsonArray);
    envThreshold(ObjData, jsonArray);

    json.insert("threshold_item_list", QJsonValue(jsonArray));
}

void BuildJson::envItem(int index, int id, const QString &name, int status, QJsonObject &json)
{
    json.insert("id",  id);
    json.insert("type_index", index); //

    json.insert("sensor", name);
    json.insert("status", status);
}

void BuildJson::envSensor(sEnvData *ObjData, QJsonArray &jsonArray)
{
    int index = 1;

     int num = ObjData->envNum;
    for(int i=0; i<num; ++i) {
        QJsonObject subObj;
        envItem(index, i, "温度", ObjData->tem[i].value, subObj);
        jsonArray.append(subObj);
    }

    index = 2;
    for(int i=0; i<num; ++i) {
        QJsonObject subObj;
        envItem(index, i, "湿度", ObjData->hum[i].value, subObj);
        jsonArray.append(subObj);
    }
}

void BuildJson::envs(sEnvData *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    envSensor(ObjData, jsonArray);

    json.insert("env_item_list", QJsonValue(jsonArray));
}

void BuildJson::alarms(QJsonObject &json)
{
    if(!mAlarmJsonArray.isEmpty())
    {
        json.insert("alarm_item_list", QJsonValue(mAlarmJsonArray));
    }

    for(int i=0; i<mAlarmJsonArray.size(); ++i) {
        mAlarmJsonArray.removeFirst();
    }
}

void BuildJson::devData(sDataPacket *packet, QJsonObject &obj)
{
    sDevData *devData = &(packet->data);
    lineData(devData, obj);
    loopData(devData, obj);
    outputData(devData, obj);
    thresholds(devData, obj);
    envs(&(devData->env), obj);
    alarms(obj);

    for(int i=0; i<6; ++i)
        obj.insert("segment"+QString::number(i+1), "");
}

