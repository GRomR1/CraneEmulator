#ifndef PORTLISTENER_H
#define PORTLISTENER_H

#include <QObject>
#include <QDebug>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QMessageBox>
#include "../Defines.h"

class PortListener : public QObject
{
    Q_OBJECT
public:
    explicit PortListener(QObject *parent = 0);

public slots:
    void setPortSettings(QString, PortSettings);    //установка настроек порта
    void sendMessage(Element el, quint8 mes);       //отправка данных в порт

signals:
    void receivedMessage(Element el, quint8 mes);
    void event(QString);                            //сигнал о событии
    void clientConnected(QString name, QString address);
                                                    //подключился клиент
private:
    QextSerialPort          *_port;                 //последовательный порт
    QByteArray               _arr;
    QByteArray               _arrForInitialize;
    QByteArray               _arrDeviceInfo;
    bool                     _bDeviceIsConnected;
    bool                     _bLocalInfoIsSended;   //пора принимать инфу о клиенте
    int                      _i;

    void connectPort();                             //подключение к порту

private slots:
    void readSocket();                              //считывание данных из порта
    void reportClose();                             //сообщить о закрытии порта
    void reportDsr(bool status);                    //сообщить о подключении/отключении устройства от порта


};

#endif // PORTLISTENER_H
