#ifndef PORTLISTENER_H
#define PORTLISTENER_H

#include <QObject>

class PortListener : public QObject
{
    Q_OBJECT
public:
    explicit PortListener(QObject *parent = 0);

signals:

public slots:

};

#endif // PORTLISTENER_H
