#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
namespace Ui {
class Configuration;
}

class Configuration : public QWidget
{
    Q_OBJECT

public:

    struct Configurations {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit Configuration(QWidget *parent = nullptr);
    ~Configuration();

    Configurations get_configuration();

signals:
    void set_configuration();

private slots:
    void on_applyButton_clicked();

private:
    Ui::Configuration *ui;
    Configurations m_currentConfigurations;
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();
};

#endif // CONFIGURATION_H
