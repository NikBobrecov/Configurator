#include "searchdevice.h"

#include "arduinodevice.h"

#include <QSerialPortInfo>

SearchDevice::SearchDevice(QObject *parent)
    : QObject{parent}
{

}

ArduinoDevice *SearchDevice::search(QObject *parent)
{
    QList<QSerialPortInfo> port_list = QSerialPortInfo::availablePorts();
    for (auto&& i : qAsConst(port_list))
    {
        if (i.description().contains("CH340"))
        {
            return new ArduinoDevice(i.portName(),parent);
        }
    }
    return nullptr;
}
