#ifndef SEARCHDEVICE_H
#define SEARCHDEVICE_H

#include <QObject>

class ArduinoDevice;
class SearchDevice : public QObject
{
    Q_OBJECT
public:
    explicit SearchDevice(QObject *parent = nullptr);

    static ArduinoDevice* search(QObject *parent = nullptr);

signals:

};

#endif // SEARCHDEVICE_H
