#include "configuration.h"
#include "ui_configuration.h"

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

Configuration::Configuration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);

    fillPortsParameters();
    fillPortsInfo();

    connect(ui->applyButton,SIGNAL(clicked()), this, SIGNAL(set_configuration()));
}

Configuration::~Configuration()
{
    delete ui;
}


Configuration::Configurations Configuration::get_configuration()
{

//    QByteArray ba;
//    ba.resize(5);
//    ba[0] = ui->baudRateBox->currentIndex();
//    ba[1] = ui->dataBitsBox->currentIndex();
//    ba[2] = ui->parityBox->currentIndex();
//    ba[3] = ui->stopBitsBox->currentIndex();
//    ba[4] = ui->flowControlBox->currentIndex();

    return m_currentConfigurations;
}

void Configuration::fillPortsParameters()
{
    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateBox->addItem(tr("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void Configuration::fillPortsInfo()
{
    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

    ui->serialPortInfoListBox->addItem(tr("Custom"));
}

void Configuration::on_applyButton_clicked()
{
    updateSettings();
}

void Configuration::updateSettings()
{
    m_currentConfigurations.name = ui->serialPortInfoListBox->currentText();

    if (ui->baudRateBox->currentIndex() == 4) {
        m_currentConfigurations.baudRate = ui->baudRateBox->currentText().toInt();
    } else {
        m_currentConfigurations.baudRate = static_cast<QSerialPort::BaudRate>(
                    ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    }
    m_currentConfigurations.stringBaudRate = QString::number(m_currentConfigurations.baudRate);

    m_currentConfigurations.dataBits = static_cast<QSerialPort::DataBits>(
                ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    m_currentConfigurations.stringDataBits = ui->dataBitsBox->currentText();

    m_currentConfigurations.parity = static_cast<QSerialPort::Parity>(
                ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    m_currentConfigurations.stringParity = ui->parityBox->currentText();

    m_currentConfigurations.stopBits = static_cast<QSerialPort::StopBits>(
                ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    m_currentConfigurations.stringStopBits = ui->stopBitsBox->currentText();

    m_currentConfigurations.flowControl = static_cast<QSerialPort::FlowControl>(
                ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
    m_currentConfigurations.stringFlowControl = ui->flowControlBox->currentText();

    m_currentConfigurations.localEchoEnabled = ui->localEchoCheckBox->isChecked();
}
