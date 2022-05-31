#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMessageBox>


QString temp;

QByteArray configArray[5];

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this))
{
    ui->setupUi(this);
    config = new Configuration();
    codec = new Codec();

    connect(config, SIGNAL(set_configuration()), this, SLOT(set_configuration_mainSlot()));


    connect(m_serial,SIGNAL(readyRead()),this,SLOT(serialReceived()));
}

MainWindow::~MainWindow()
{
    delete ui;
    m_serial->close();
}

void MainWindow::serialReceived()
{
    temp = QString(m_serial->readAll()+temp);
    ui->serialRead->setPlainText(temp);
    qDebug()<<temp;
}
void MainWindow::serialWriteData(const QByteArray &data)
{
    m_serial->write(data);
}


void MainWindow::on_actionConnect_triggered()
{
    ui->statusbar->showMessage("baglantı acıldı", 2000);
    openSerialPort();
}


void MainWindow::on_actionDisconnect_triggered()
{
    ui->statusbar->showMessage("baglantı koparıldı", 2000);
    closeSerialPort();
}


void MainWindow::on_actionClear_triggered()
{
    ui->statusbar->showMessage("temizleme acıldı", 2000);
    ui->serialRead->clear();
}


void MainWindow::on_actionAbout_triggered()
{
    ui->statusbar->showMessage("hakkında acıldı", 2000);
    about();
}


void MainWindow::on_actionConfig_triggered()
{
    ui->statusbar->showMessage("konfigurasyon acıldı acıldı", 2000);
    config->show();
}


void MainWindow::on_actionData_Codec_triggered()
{
    ui->statusbar->showMessage("codec acıldı acıldı", 2000);
    codec->show();
}

void MainWindow::set_configuration_mainSlot()
{
    ui->statusbar->showMessage("konfigurasyon ayarları yapıldı", 2000);
    config->close();
}

void MainWindow::openSerialPort()
{
//    m_serial = new QSerialPort(this);
//    m_serial->setPortName("com6");
//    m_serial->setBaudRate(QSerialPort::Baud9600);
//    m_serial->setDataBits(QSerialPort::Data8);
//    m_serial->setParity(QSerialPort::NoParity);
//    m_serial->setStopBits(QSerialPort::OneStop);
//    m_serial->setFlowControl(QSerialPort::NoFlowControl);
//    m_serial->open(QIODevice::ReadWrite);
//    m_serial->write("OK");


    const Configuration::Configurations p = config->get_configuration();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);


    if (m_serial->open(QIODevice::ReadWrite)) {
//        m_console->setEnabled(true);
//        m_console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfig->setEnabled(false);
        ui->statusbar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        ui->statusbar->showMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
//    m_console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfig->setEnabled(true);
    ui->statusbar->showMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Embedded Terminal"),
                       tr("The <b>Embedded Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::on_serialSendButton_clicked()
{
    QString str = ui->serialSend->toPlainText();
    QByteArray br = str.toUtf8();
    serialWriteData(br);
}

