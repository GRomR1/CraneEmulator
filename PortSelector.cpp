#include "PortSelector.h"
#include "ui_PortSelector.h"

PortSelector::PortSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelector)
{
    ui->setupUi(this);
    //получение доступных последовательных портов в системе
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach(QextPortInfo port, ports)
    {
        ui->_comboBoxPortName->addItem(port.portName);
    }

    //запись возможных скоростей передачи данных
    // "2400" << "4800" << "9600" << "14400" << "19200" << "38400" << "57600" << "115200"

    //запись возможных типов контроля передачи
    // "OFF" << "HARDWARE" << "XON/XOFF";

    //запись возможных паритетов
    // "NONE" << "ODD" << "EVEN" << "MARK" << "SPACE";

    //запись возможных битов данных
    // "5" << "6" << "7" << "8";

    //запись возможных стоповых битов
    // "1" << "1.5" << "2";
    setWindowFlags(Qt::WindowCloseButtonHint);
}

PortSelector::~PortSelector()
{
    delete ui;
}

void PortSelector::on_buttonBox_accepted()
{
    QString portName = ui->_comboBoxPortName->currentText();
    emit accepted(portName, getPortSettings());
    this->accept();
}

PortSettings PortSelector::getPortSettings()
{
    PortSettings settings;
    settings.FlowControl = FlowType( ui->_comboBoxFlowControl->currentIndex() );
    settings.Parity = ParityType( ui->_comboBoxParity->currentIndex() );
    settings.DataBits = DataBitsType( ui->_comboBoxDataBits->currentText().toInt() );
    settings.StopBits = StopBitsType( ui->_comboBoxStopBits->currentIndex() );
    settings.BaudRate = BaudRateType( ui->_comboBoxBaudRate->currentText().toInt() );

    return settings;
}
