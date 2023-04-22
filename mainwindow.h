#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>

class ArduinoDevice;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void searchDevice();
    void setDevice(ArduinoDevice *device);

private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    ArduinoDevice *m_device;
};
#endif // MAINWINDOW_H
