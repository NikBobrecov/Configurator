#ifndef ARDUINODEVICE_H
#define ARDUINODEVICE_H

#include <QObject>

#include "arduinosettings.h"

class QSerialPort;
class ArduinoDevice : public QObject
{
    Q_OBJECT
public:
    enum class State
    {
        Read,
        Write,
        Ready,
        Error,
    };

    explicit ArduinoDevice(const QString &portName, QObject *parent = nullptr);

    void saveSetting(const ArduinoSettings &setting);
    void init();

    State state() const;

    QString lastError() const;

    ArduinoSettings settings() const;

signals:

    void stateChanged();

private:
    void readData();
    void setState(State newState);

private:
    QSerialPort *m_serialPort;
    State m_state;
    ArduinoSettings m_settings;
    QString m_lastError;
    QByteArray m_buffer;

};

#endif // ARDUINODEVICE_H
