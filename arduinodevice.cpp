#include "arduinodevice.h"

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QDebug>

ArduinoDevice::ArduinoDevice(const QString &portName, QObject *parent)
    : QObject{parent}
    , m_serialPort(new QSerialPort(portName))
{
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    connect(m_serialPort, &QSerialPort::readyRead, this, &ArduinoDevice::readData);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError err){
        m_lastError = QString("Ошибка сериал порта: %1").arg(err);
        setState(State::Error);
    });


    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        m_lastError = "Не удалось подключится к порту: " + m_serialPort->errorString();
        setState(State::Error);
        return;
    }
}

void ArduinoDevice::saveSetting(const ArduinoSettings &setting)
{
    setState(State::Write);
    m_serialPort->write(setting.toJson());
    m_serialPort->flush();
}

void ArduinoDevice::init()
{
    setState(State::Write);
    m_serialPort->write("w");
    m_serialPort->flush();
}

void ArduinoDevice::readData()
{
    setState(State::Read);
    char ch;
    while (!m_serialPort->atEnd()) {
        m_serialPort->read(&ch,1);
        qDebug() << ch;
        m_buffer.append(ch);
        if (ch == '}')
        {
            m_settings = ArduinoSettings::fromJson(m_buffer);
            m_buffer.clear();
            setState(State::Ready);
            return;
        }
    }
}

ArduinoSettings ArduinoDevice::settings() const
{
    return m_settings;
}

QString ArduinoDevice::lastError() const
{
    return m_lastError;
}

ArduinoDevice::State ArduinoDevice::state() const
{
    return m_state;
}

void ArduinoDevice::setState(State newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}
