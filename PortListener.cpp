#include "PortListener.h"

PortListener::PortListener(QObject *parent) :
    QObject(parent),
    _bDeviceIsConnected(false),
    _bLocalInfoIsSended(false)
{
    _port = new QextSerialPort();    //создание порта
    _port->open(QIODevice::NotOpen); //открытие порта
    _i = 0;
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
    connect(_port, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(_port, SIGNAL(aboutToClose()), this, SLOT(reportClose()));
    connect(_port, SIGNAL(dsrChanged(bool)), this, SLOT(reportDsr(bool)));

//    if(!(_port->lineStatus() && LS_DSR))
//    {
//        QMessageBox::warning(0,tr("Предупреждение"),tr("Устройство не подключено"));
//    }
}

void PortListener::readSocket()
{
    QByteArray arr = _port->readAll();
    //qDebug() << _i++ << ": " << arr.size();

    if(_bDeviceIsConnected)
    {
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
    else
    {
        _arrForInitialize+=arr;
        if(!_bLocalInfoIsSended)
        {
            while((size_t)_arrForInitialize.size()>=sizeof(quint64))
            {
                QByteArray newArr(_arrForInitialize); //хранит массив 64 бита
                newArr.truncate(sizeof(quint64));
                //qDebug() << "received: " << newArr.toHex();
                if(newArr == QByteArray::fromHex(QByteArray::number(Preamble, 16)))
                {
                    //пора читать инфу
                    _bLocalInfoIsSended = true;
                    _arrForInitialize.remove(0,sizeof(quint64));
                    break;
                }
                _arrForInitialize.remove(0,1);
            }
        }
        else
        {
            while((size_t)_arrForInitialize.size()>=sizeof(quint64))
            {
                QByteArray newArr(_arrForInitialize);
                newArr.truncate(sizeof(quint64));
                //qDebug() << "received: " << newArr.toHex();
                if(newArr == QByteArray::fromHex(QByteArray::number(Preamble, 16)))
                {
                    //инфа прочитана
                    _bLocalInfoIsSended = false;
                    _arrForInitialize.remove(0,sizeof(quint64));
                    _bDeviceIsConnected = true;
                    QDataStream in(&_arrDeviceInfo, QIODevice::ReadOnly);
                    QString name;
                    QString addr;
                    in >> name >> addr;
                    //qDebug() << "Info is readed: " << _arrDeviceInfo.toHex() << "[" << _arrDeviceInfo.size() << "]";
                    //qDebug() << name << addr;
                    emit clientConnected(name, addr);
                    break;
                }
                _arrDeviceInfo += _arrForInitialize.left(1);
                _arrForInitialize.remove(0,1);
            }
        }
    }
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
