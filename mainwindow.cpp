#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "arduinodevice.h"
#include "searchdevice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_timer, &QTimer::timeout, this, &MainWindow::searchDevice);
    m_timer.start(500);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchDevice()
{
    ArduinoDevice *d = SearchDevice::search(this);
    if (!d)
        return;

    m_timer.stop();
    setDevice(d);

}

void MainWindow::setDevice(ArduinoDevice *device)
{
    m_device = device;
    connect(m_device, &ArduinoDevice::stateChanged, this, [this]()
            {
                switch (m_device->state()) {
                case ArduinoDevice::State::Read: {ui->label_state->setText("Чтение"); ui->pushButton_saveSetting->setEnabled(false); return;}
                case ArduinoDevice::State::Write: {ui->label_state->setText("Запись"); ui->pushButton_saveSetting->setEnabled(false); return;}
                case ArduinoDevice::State::Ready: {ui->label_state->setText("Готово"); ui->pushButton_saveSetting->setEnabled(true); return;}
                case ArduinoDevice::State::Error:
                    break;
                }
            });

    m_device->init();
}

