#ifndef PORTSELECTOR_H
#define PORTSELECTOR_H

#include <QDialog>
#include <QDebug>
#include <qextserialport.h>
#include <qextserialenumerator.h>

#include <QtWidgets>

namespace Ui {
class PortSelector;
}

class PortSelector : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelector(QWidget *parent = 0);
    PortSettings getPortSettings();    //получение настроек порта
    ~PortSelector();

signals:
    void accepted(QString portName, PortSettings settings);  //принять настройки порта

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PortSelector *ui;
    QComboBox cb;
};

#endif // PORTSELECTOR_H
