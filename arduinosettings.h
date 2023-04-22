#ifndef ARDUINOSETTINGS_H
#define ARDUINOSETTINGS_H

#include <QString>

struct ArduinoSettings
{
    QString apn;
    QString user;
    QString password;
    QString server;
    int port;
    int timeout;

    QByteArray toJson() const;
    static ArduinoSettings fromJson(const QByteArray &json);


public:
    QString imei() const;

private:
    QString m_imei;

};

#endif // ARDUINOSETTINGS_H
