#include "arduinosettings.h"

#include <QJsonDocument>
#include <QJsonObject>



QByteArray ArduinoSettings::toJson() const
{
    /*{"apn":"internet.mts.ru","gprsUser":"mts","gprsPass":"mts","server":"83.69.9.128","port":11111,"timeOutSM":30000}*/
    QJsonObject obj;
    obj.insert("apn",apn);
    obj.insert("gprsUser",user);
    obj.insert("gprsPass",password);
    obj.insert("server",server);
    obj.insert("port",port);
    obj.insert("timeOutSM",timeout);
    return QJsonDocument(obj).toJson();

}

ArduinoSettings ArduinoSettings::fromJson(const QByteArray &json)
{
    ArduinoSettings obj;
    auto &&d = QJsonDocument::fromJson(json);
    auto &&jObj = d.object();
    obj.apn = jObj.value("apn").toString();
    obj.user = jObj.value("gprsUser").toString();
    obj.password = jObj.value("gprsPass").toString();
    obj.server = jObj.value("server").toString();
    obj.port = jObj.value("port").toInt();
    obj.timeout = jObj.value("timeOutSM").toInt();
    obj.m_imei = jObj.value("IMEI").toString();
    return obj;
}

QString ArduinoSettings::imei() const
{
    return m_imei;
}
