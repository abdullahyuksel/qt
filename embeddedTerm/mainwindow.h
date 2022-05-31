#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <configuration.h>
#include <codec.h>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialReceived();
    void serialWriteData(const QByteArray &data);
    void on_actionConnect_triggered();

    void on_actionDisconnect_triggered();

    void on_actionClear_triggered();

    void on_actionAbout_triggered();

    void on_actionConfig_triggered();

    void on_actionData_Codec_triggered();

    void set_configuration_mainSlot();
    void on_serialSendButton_clicked();

private:
    Ui::MainWindow *ui;
    Configuration *config;
    Codec *codec;
    QSerialPort *m_serial = nullptr;

    void openSerialPort();
    void closeSerialPort();
    void about();
};
#endif // MAINWINDOW_H
