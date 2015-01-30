#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CraneWidget.h"
#include "PortSelector.h"
#include "PortListener.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void translateMessage(Element,quint8);

private:
    PortSelector *portSelector;
    PortListener *portListener;
    CraneWidget *craneWidget;
    Ui::MainWindow *ui;

private slots:
    void sendPowerOn();
    void sendPowerOff();
    void sendLightOn();
    void sendLightOff();
    void sendTemperatureHigh();
    void sendTemperatureNormal();
    void sendHookIsWarning();
    void sendHookIsNormal();
    void on_actionAbout_triggered();                    //показ О программе
};

#endif // MAINWINDOW_H
