#include "PortListener.h"

PortListener::PortListener(QObject *parent) :
    QObject(parent)
{
    _port = new QextSerialPort();    //создание порта
    _port->open(QIODevice::NotOpen); //открытие порта
}

void PortListener::setPortSettings(QString PortName, PortSettings settings)
{
    //установка параметров порта
    _port->setPortName(PortName);
    _port->setBaudRate(settings.BaudRate);
    _port->setDataBits(settings.DataBits);
    _port->setFlowControl(settings.FlowControl);
    _port->setParity(settings.Parity);
    _port->setStopBits(settings.StopBits);

    connectPort();    //соединение с портом
}

void PortListener::connectPort()
{
    //открытие порта
    _port->open(QIODevice::ReadWrite);
    connect(_port, SIGNAL(readyRead()), this, SLOT(receive()));
    connect(_port, SIGNAL(aboutToClose()), this, SLOT(reportClose()));
    connect(_port, SIGNAL(dsrChanged(bool)), this, SLOT(reportDsr(bool)));

//    if(!(_port->lineStatus() && LS_DSR))
//    {
//        QMessageBox::warning(0,tr("Предупреждение"),tr("Устройство не подключено"));
//    }
}

void PortListener::receive()
{
    QByteArray arr = _port->readAll();
    if(QByteArray(_arr+arr).size()>=2)
    {
        while(arr.size()>0)
        {
            QByteArray newArr(arr);
            if(_arr.size()==0)
            {
                newArr.truncate(2);
                _arr=newArr;
                arr.remove(0,2);
            }
            else
            {   //if(_arr.size()==1)
                newArr.truncate(1);
                _arr=_arr+newArr;
                arr.remove(0,1);
            }
            if(_arr.size()>=2)
            {
                QDataStream in(&_arr, QIODevice::ReadOnly);
                quint8 el;
                quint8 mes;
                in >> el >> mes;
                emit receivedMessage((Element)el, mes);
                qDebug() << "readed from port: " << _arr.toHex();
                _arr.clear();
            }
        }
    }
    else
       _arr+=arr;
}

void PortListener::sendMessage(Element el, quint8 mes)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint8(el) << mes;

    qDebug() << "write to port: " << arrBlock.toHex();

    _port->write( arrBlock.data(), arrBlock.size() );
}

void PortListener::reportClose()
{
    emit event(tr("Закрытие порта"));
    QMessageBox::information(0,tr("Внимание"),tr("Закрытие порта"));
}

void PortListener::reportDsr(bool status)
{
    if(status)
    {
        emit event(tr("Устройство подключено"));
        QMessageBox::information(0,tr("Внимание"),tr("Устройство подключено"));
    }
    else
    {
        emit event(tr("Устройство отключено"));
        QMessageBox::information(0,tr("Внимание"),tr("Устройство отключено"));
    }
}
