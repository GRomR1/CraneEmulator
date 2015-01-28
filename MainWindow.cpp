#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    portSelector = new PortSelector();
    portListener = new PortListener();
    craneWidget = new CraneWidget();

    portSelector->show();
    connect(portSelector, SIGNAL(accepted()),
            this, SLOT(show()));
    connect(portSelector, SIGNAL(accepted(QString,PortSettings)),
            portListener, SLOT(setPortSettings(QString,PortSettings)));
    connect(portListener, SIGNAL(receivedMessage(Element,quint8)),
            this, SLOT(translateMessage(Element,quint8)));

    connect(craneWidget, SIGNAL(signalPowerOn()),
            this, SLOT(sendPowerOn()));
    connect(craneWidget, SIGNAL(signalPowerOff()),
            this, SLOT(sendPowerOff()));
    connect(craneWidget, SIGNAL(signalLightOn()),
            this, SLOT(sendLightOn()));
    connect(craneWidget, SIGNAL(signalLightOff()),
            this, SLOT(sendLightOff()));
    connect(craneWidget, SIGNAL(temperatureHigh()),
            this, SLOT(sendTemperatureHigh()));
    connect(craneWidget, SIGNAL(temperatureNormal()),
            this, SLOT(sendTemperatureNormal()));
    connect(craneWidget, SIGNAL(hookIsWarning()),
            this, SLOT(sendHookIsWarning()));
    connect(craneWidget, SIGNAL(hookIsNormal()),
            this, SLOT(sendHookIsNormal()));

    connect(portListener, SIGNAL(clientConnected(QString,QString)),
            craneWidget, SLOT(setClientInfo(QString,QString)));
    setCentralWidget(craneWidget);
}

MainWindow::~MainWindow()
{
    delete portSelector;
    delete portListener;
    delete craneWidget;
    delete ui;
}


void MainWindow::translateMessage(Element el,quint8 mes)
{
    switch (el) {
    case powerButton:
        craneWidget->powerOn(mes);
        break;
    case lightButton:
        craneWidget->lightOn(mes);
        break;
    case soundSignal:
        craneWidget->soundSignalOn(mes);
        break;
    case pillarUp:
        craneWidget->pillarUp(mes);
        break;
    case pillarDown:
        craneWidget->pillarDown(mes);
        break;
    case derrickUp:
        craneWidget->derrickUp(mes);
        break;
    case derrickDown:
        craneWidget->derrickDown(mes);
        break;
    case outriggerUp:
        craneWidget->outriggerUp(mes);
        break;
    case outriggerDown:
        craneWidget->outriggerDown(mes);
        break;
    case telescopicUp:
        craneWidget->telescopicUp(mes);
        break;
    case telescopicDown:
        craneWidget->telescopicDown(mes);
        break;
    case hookUp:
        craneWidget->hookUp(mes);
        break;
    case hookDown:
        craneWidget->hookDown(mes);
        break;
    case leftCrutchUp:
        craneWidget->leftCrutchUp(mes);
        break;
    case leftCrutchDown:
        craneWidget->leftCrutchDown(mes);
        break;
    case rightCrutchUp:
        craneWidget->rightCrutchUp(mes);
        break;
    case rightCrutchDown:
        craneWidget->rightCrutchDown(mes);
        break;
    default:
        break;
    }
}


void MainWindow::sendPowerOn()
{
    portListener->sendMessage(powerStatus, 0x01);
}

void MainWindow::sendPowerOff()
{
    portListener->sendMessage(powerStatus, 0x00);
}

void MainWindow::sendLightOn()
{
    portListener->sendMessage(lightStatus, 0x01);
}

void MainWindow::sendLightOff()
{
    portListener->sendMessage(lightStatus, 0x00);
}

void MainWindow::sendTemperatureHigh()
{
    portListener->sendMessage(highTemperature, 0x01);
}

void MainWindow::sendTemperatureNormal()
{
    portListener->sendMessage(highTemperature, 0x00);
}

void MainWindow::sendHookIsWarning()
{
    portListener->sendMessage(hookWarning, 0x01);
}

void MainWindow::sendHookIsNormal()
{
    portListener->sendMessage(hookWarning, 0x00);
}
