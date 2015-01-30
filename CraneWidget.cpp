#include "CraneWidget.h"
#include "ui_CraneWidget.h"

static const int multiplier = 10; //множитель шагов

CraneWidget::CraneWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CraneWidget),
    _itemEllipseForDebug(0)
{
    ui->setupUi(this);
    _scene = new GraphicsScene(QRectF(0, 30, 220, 150));
    _sceneTop = new GraphicsScene(QRectF(-18, 30, 170, 170));
    QSvgRenderer *renderer = new QSvgRenderer(QString(":/Кран_ВидCбоку.svg"));
    QSvgRenderer *rendererTop = new QSvgRenderer(QString(":/Кран_ВидСверху.svg"));
//    QGraphicsSvgItem *item1Top = new QGraphicsSvgItem(QString(":/Кран_ВидСверху.svg"));

//    qDebug() << renderer->elementExists("pillar") << renderer->elementExists("hook") << "";
//    qDebug() << renderer->boundsOnElement("pillar").topLeft() << renderer->boundsOnElement("hook").topLeft();
    _groundTop = new Top::OtherItem(AbstractItems::Ground, rendererTop);
    _groundTop->setId("ground");
    _groundTop->setZValue(-1.0);
    _sceneTop->addItem(_groundTop);

    _leftCrutch = new Side::CrutchItem(AbstractItems::LeftCrutch, renderer);
    _leftCrutch->setMax(6.8);
    _leftCrutch->setCountSteps(5*multiplier);
    ui->_verticalSliderLeftCrutch->setMaximum(5*multiplier);
    ui->_verticalSliderLeftCrutch->setSingleStep(1);

    _rightCrutch = new Side::CrutchItem(AbstractItems::RightCrutch, renderer);
    _rightCrutch->setMax(6.8);
    _rightCrutch->setCountSteps(5*multiplier);
    ui->_verticalSliderRightCrutch->setMaximum(5*multiplier);
    ui->_verticalSliderRightCrutch->setSingleStep(1);

    _pillar = new Side::PillarItem(renderer);
    _pillar->setMin(-45);
    _pillar->setMax(45);
    _pillar->setCountSteps(18*multiplier);
    ui->_verticalSliderPillar->setMaximum(9*multiplier/2);
    ui->_verticalSliderPillar->setMinimum(-9*multiplier/2);
    ui->_verticalSliderPillar->setSingleStep(1);
    ui->_verticalSliderPillar->setValue(0);

    _pillarTop = new Top::PillarItem(rendererTop);
    _pillarTop->setMin(-45);
    _pillarTop->setMax(45);
    _pillarTop->setCountSteps(18*multiplier);
    _sceneTop->addItem(_pillarTop);

    _ellipseDerrick = new Side::OtherItem(AbstractItems::EllipseDerick, renderer);
    _ellipseDerrick->setId("ellipse_derrick");

    _pillarRectTop = new Top::OtherItem(AbstractItems::RectPillar, rendererTop);
    _pillarRectTop->setId("rect_pillar");
    _sceneTop->addItem(_pillarRectTop);

    _derrick = new Side::DerrickItem(renderer);
    _derrick->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _derrick->setMax(30);
    _derrick->setMin(0);
    _derrick->setCountSteps(15*multiplier);
    _derrick->setParentItemMy(_pillar);
    ui->_verticalSliderDerrick->setMaximum(15*multiplier);
    ui->_verticalSliderDerrick->setSingleStep(1);

    _derrickTop = new Top::DerrickItem(rendererTop);
    _derrickTop->setMax(30);
    _derrickTop->setMin(0);
    _derrickTop->setCountSteps(15*multiplier);
    _derrickTop->setParentItemMy(_pillarTop);
    _sceneTop->addItem(_derrickTop);

    _ellipseOutrigger = new Side::EllipseOutriggerItem(renderer);
    _ellipseOutrigger->setParentItemMy(_derrick);
    _scene->addItem(_ellipseOutrigger);

    _outrigger = new Side::OutriggerItem(renderer);
    _outrigger->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _outrigger->setMax(0);
    _outrigger->setMin(-30);
    _outrigger->setCountSteps(15*multiplier);
    _outrigger->setParentItemMy(_ellipseOutrigger);
    _outriggerTop = new Top::OutriggerItem(rendererTop);
//    _outriggerTop->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _outriggerTop->setMax(0);
    _outriggerTop->setMin(-30);
    _outriggerTop->setCountSteps(15*multiplier);
    _outriggerTop->setParentItemMy(_derrickTop);
    _outriggerTop->setZValue(1.0);
    _sceneTop->addItem(_outriggerTop);
    ui->_verticalSliderOutrigger->setMaximum(15*multiplier);
    ui->_verticalSliderOutrigger->setValue(15*multiplier);
    ui->_verticalSliderOutrigger->setSingleStep(1);

    _telescopic = new Side::TelescopicItem(renderer);
    _telescopic->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _telescopic->setMax(20);
    _telescopic->setMin(0);
    _telescopic->setCountSteps(10*multiplier);
    ui->_verticalSliderTelescopic->setMaximum(10*multiplier);
    ui->_verticalSliderTelescopic->setValue(0);
    ui->_verticalSliderTelescopic->setSingleStep(1);
    _telescopic->setParentItemMy(_outrigger);

    _telescopicTop = new Top::TelescopicItem(rendererTop);
//    _telescopicTop->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _telescopicTop->setMax(20);
    _telescopicTop->setMin(0);
    _telescopicTop->setCountSteps(10*multiplier);
    _telescopicTop->setParentItemMy(_outriggerTop);
    _sceneTop->addItem(_telescopicTop);

    _ellipseHook = new Side::EllipseHookItem(renderer);
    _ellipseHook->setParentItemMy(_telescopic);

    _ropeHook = new Side::RopeHookItem(renderer);
    _ropeHook->setParentItemMy(_ellipseHook);
    _ropeHook->setMax(51);
    _ropeHook->setMin(1);
    _ropeHook->setCountSteps(20*multiplier);
    _ropeHook->setValue(1.1);
    ui->_verticalSliderRopeHook->setMaximum(20*multiplier);
    ui->_verticalSliderRopeHook->setSingleStep(1);
    connect(_ropeHook, SIGNAL(minIsReached()),
            this, SLOT(showHookWarning()));
    connect(_ropeHook, SIGNAL(stopMinIsReached()),
            this, SLOT(stopHookWarning()));

    _hook = new Side::HookItem(renderer);
    _hook->setParentItemMy(_ropeHook);

    _ground = new Side::OtherItem(AbstractItems::Ground, renderer);
    _ground->setId("ground");

    _lightOn = new Side::LightItem(AbstractItems::LightOn, renderer);
    _lightOn->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _lightOn->setParentItemMy(_telescopic);
    _lightOnTop = new Top::LightItem(rendererTop);
//    _lightOnTop->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _lightOnTop->setParentItemMy(_telescopicTop);
    _lightOnTop->setZValue(-0.5);
    _sceneTop->addItem(_lightOnTop);
    _lightOn->setVisible(false);
    _lightOnTop->setVisible(false);

    _lampLight = new Side::LightItem(AbstractItems::LampLight, renderer);
    _lampLight->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _lampLight->setParentItemMy(_telescopic);

    _scene->addItem(_leftCrutch);
    _scene->addItem(_rightCrutch);
    _scene->addItem(_lightOn);
    _scene->addItem(_lampLight);
    _scene->addItem(_ropeHook);
    _scene->addItem(_hook);
    _scene->addItem(_telescopic);
    _scene->addItem(_ellipseHook);
    _scene->addItem(_derrick);
    _scene->addItem(_outrigger);
    _scene->addItem(_pillar);
    _scene->addItem(_ellipseDerrick);
    _scene->addItem(_ground);

    qreal x=_ground->mapToScene(QPointF(0,0)).x();
    qreal y=_ground->mapToScene(QPointF(0,0)).y() + _ground->boundingRect().height();
    QRectF rect(x, 30, _ground->boundingRect().width(), y-30);
    _scene->setSceneRect(rect);
    _scene->addRect(rect, QPen(Qt::green));
    QRectF rectWhite(x,rect.y()+rect.height(), rect.width(),100);
    _scene->addRect(rectWhite, QPen(Qt::NoPen), QBrush(Qt::white));
    ui->_view->setSceneRect(rect);
    ui->_view->setScene(_scene);

    y=_derrickTop->pos().y()+_derrickTop->boundingRect().height()/2;
    QRectF rect2(-14, y-110, _ground->boundingRect().width(), 2*110);
    _sceneTop->setSceneRect(rect2);
    _sceneTop->addRect(_sceneTop->sceneRect(), QPen(Qt::green));
    ui->_viewTop->setScene(_sceneTop);
    qreal scaleGroundX = rect2.width() / _groundTop->boundingRect().width();
    QTransform t;
    t.scale(scaleGroundX,1);
    _groundTop->setTransform(t);
    _groundTop->setPos(rect2.x(), rendererTop->boundsOnElement("ground").topLeft().y());

//    _scene->addLine(QLineF(0, 0, 300, 0), QPen(Qt::green, 0.5)); //horizontal (y1==y2)
//    _scene->addLine(QLineF(0, 0, 0, 200), QPen(Qt::green, 0.5)); //vertical (x1==x2)

    QPointF p(0,0);
    _itemEllipse = _scene->addEllipse(QRectF(p.x(),p.y(),1,1), QPen(Qt::NoPen), QBrush(Qt::red));

    QPointF p2(0,0);
//    p2=_derrickTop->pos();
    _itemEllipseTop = _sceneTop->addEllipse(QRectF(p2.x(),p2.y(),1,1), QPen(Qt::NoPen), QBrush(Qt::red));
    connect(_scene, SIGNAL(clicked(QPointF)),
            this, SLOT(sceneClicked(QPointF)));
    connect(_sceneTop, SIGNAL(clicked(QPointF)),
            this, SLOT(sceneTopClicked(QPointF)));
    ui->_verticalSliderScale->setValue(25);

    QString str = ui->_labelClientInfo->text();
    ui->_labelClientInfo->setText("<FONT COLOR = RED>"+str+"</FONT>");


    _soundSignal = new QSound(":/sound1.wav");
    _soundSignal->setLoops(QSound::Infinite);
}

CraneWidget::~CraneWidget()
{
    delete ui;
}

void CraneWidget::powerOn(bool b)
{
    if(b)
    {
        ui->_pushButtonPower->setStyleSheet("color: green;  font-weight: bold");
#ifdef TURN_IMMEDIATELY
        ui->_pushButtonPower->click();
#endif
    }
    else
    {
        ui->_pushButtonPower->setStyleSheet("color: black;  font-weight: normal");
#ifdef TURN_IMMEDIATELY
        ui->_pushButtonPower->click();
#endif
    }

}

void CraneWidget::lightOn(bool b)
{
    if(b)
    {
        ui->_pushButtonLight->setStyleSheet("color: green;  font-weight: bold");
#ifdef TURN_IMMEDIATELY
        ui->_pushButtonLight->click();
#endif
    }
    else
    {
        ui->_pushButtonLight->setStyleSheet("color: black;  font-weight: normal");
#ifdef TURN_IMMEDIATELY
        ui->_pushButtonLight->click();
#endif
    }
}

void CraneWidget::soundSignalOn(bool b)
{
    if(b)
    {
        ui->_pushButtonSoundSignal->setStyleSheet("color: red;  font-weight: bold");
        _soundSignal->play();
    }
    else
    {
        ui->_pushButtonSoundSignal->setStyleSheet("color: black;  font-weight: normal");
        _soundSignal->stop();
    }
}

void CraneWidget::pillarUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonPillarMinus_clicked();
}

void CraneWidget::pillarDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonPillarPlus_clicked();
}

void CraneWidget::derrickUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonDerrickRotatePlus_clicked();
}

void CraneWidget::derrickDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonDerrickRotateMinus_clicked();
}

void CraneWidget::outriggerUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonOutriggerRotatePlus_clicked();
}

void CraneWidget::outriggerDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonOutriggerRotateMinus_clicked();
}

void CraneWidget::telescopicUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonTelescopicPlus_clicked();
}

void CraneWidget::telescopicDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonTelescopicMinus_clicked();
}

void CraneWidget::hookUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonRopeHookMinus_clicked();
}

void CraneWidget::hookDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonRopeHookPlus_clicked();
}

void CraneWidget::leftCrutchUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonLeftCrutchMinus_clicked();
}

void CraneWidget::leftCrutchDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonLeftCrutchPlus_clicked();
}

void CraneWidget::rightCrutchUp(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonRightCrutchMinus_clicked();
}

void CraneWidget::rightCrutchDown(int value)
{
    for(int i=0; i<value; i++)
        on__pushButtonRightCrutchPlus_clicked();
}


void CraneWidget::on__verticalSliderScale_valueChanged(int value)
{
    ui->_view->resetTransform();
    ui->_view->scale(value*1.0/10,value*1.0/10);
    ui->_viewTop->resetTransform();
    ui->_viewTop->scale(value*1.0/10,value*1.0/10);
}

void CraneWidget::addText(QString txt)
{
    ui->_ptEdit->appendPlainText(txt);
    ui->_ptEdit->centerCursor();
}

void CraneWidget::sceneClicked(QPointF point)
{
    QString str;
    str+="x=";
    qreal x=point.x();
    str+=QString().setNum(x);
    str+=" y=";
    qreal y=point.y();
    str+=QString().setNum(y);

    _itemEllipse->setPos(x-_itemEllipse->boundingRect().width()/2,
                         y-_itemEllipse->boundingRect().height()/2);

    addText(str);
}

void CraneWidget::sceneTopClicked(QPointF point)
{
    QString str;
    str+="x=";
    qreal x=point.x();
    str+=QString().setNum(x);
    str+=" y=";
    qreal y=point.y();
    str+=QString().setNum(y);

    _itemEllipseTop->setPos(x-_itemEllipseTop->boundingRect().width()/2,
                         y-_itemEllipseTop->boundingRect().height()/2);

//    qDebug() << point;
//    qDebug() << _derrickTop->transformOriginPoint();
//    _derrickTop->setTransformOriginPoint(point);
    addText(str);
}

void CraneWidget::setClientInfo(QString name, QString address)
{
    QString str = "Client connected: " + name + " (" + address + ")";
    ui->_labelClientInfo->setText("<FONT COLOR = GREEN>"+str+"</FONT>");
}

void CraneWidget::drawPoint(QPointF p)
{
    if(_itemEllipseForDebug)
    {
        _scene->removeItem(_itemEllipseForDebug);
        delete _itemEllipseForDebug;
        _itemEllipseForDebug=0;
    }

    _itemEllipseForDebug = _scene->addEllipse(QRectF(p.x(),p.y(),1,1), QPen(Qt::NoPen), QBrush(Qt::green));
}

void CraneWidget::showHookWarning()
{
    ui->_pushButtonHookWarning->setStyleSheet("color: red;  font-weight: bold");
    emit hookIsWarning();
}

void CraneWidget::stopHookWarning()
{
    ui->_pushButtonHookWarning->setStyleSheet("color: black;  font-weight: normal");
    emit hookIsNormal();
}

void CraneWidget::on__pushButtonDerrickRotatePlus_clicked()
{
    QString mes("derrick +");
//    _derrick->increment();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() +
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonDerrickRotateMinus_clicked()
{
    QString mes("derrick -");
//    _derrick->decrement();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() -
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonOutriggerRotatePlus_clicked()
{
    QString mes("outrigger +");
//    _outrigger->increment();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() +
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonOutriggerRotateMinus_clicked()
{
    QString mes("outrigger -");
//    _outrigger->decrement();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() -
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonRopeHookPlus_clicked()
{
    QString mes("rope hook +");
    ui->_verticalSliderRopeHook->setValue(
                ui->_verticalSliderRopeHook->value() +
                ui->_verticalSliderRopeHook->singleStep());
//    _ropeHook->increment();
    addText(mes);
}


void CraneWidget::on__pushButtonRopeHookMinus_clicked()
{
    QString mes("rope hook -");
    ui->_verticalSliderRopeHook->setValue(
                ui->_verticalSliderRopeHook->value() -
                ui->_verticalSliderRopeHook->singleStep());
//    _ropeHook->decrement();
    addText(mes);
}
void CraneWidget::on__pushButtonTelescopicPlus_clicked()
{
    QString mes("telescopic +");
//    _telescopic->increment();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() +
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonTelescopicMinus_clicked()
{
    QString mes("telescopic -");
//    _telescopic->decrement();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() -
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonLeftCrutchPlus_clicked()
{
    QString mes("left crutch +");
//    _leftCrutch->increment();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() +
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonLeftCrutchMinus_clicked()
{
    QString mes("left crutch -");
//    _leftCrutch->decrement();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() -
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonRightCrutchPlus_clicked()
{
    QString mes("right crutch +");
//    _rightCrutch->increment();
    ui->_verticalSliderRightCrutch->setValue(
                ui->_verticalSliderRightCrutch->value() +
                ui->_verticalSliderRightCrutch->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonRightCrutchMinus_clicked()
{
    QString mes("right crutch -");
//    _rightCrutch->decrement();
    ui->_verticalSliderRightCrutch->setValue(
                ui->_verticalSliderRightCrutch->value() -
                ui->_verticalSliderRightCrutch->singleStep());
    addText(mes);
}

void CraneWidget::on__pushButtonPillarPlus_clicked()
{
    QString mes("pillar +");
    ui->_verticalSliderPillar->setValue(
                ui->_verticalSliderPillar->value() +
                ui->_verticalSliderPillar->singleStep());
//    _pillar->increment();
    addText(mes);
}

void CraneWidget::on__pushButtonPillarMinus_clicked()
{
    QString mes("pillar -");
    ui->_verticalSliderPillar->setValue(
                ui->_verticalSliderPillar->value() -
                ui->_verticalSliderPillar->singleStep());
//    _pillar->decrement();
    addText(mes);
}

void CraneWidget::on__verticalSliderRopeHook_valueChanged(int value)
{
    QString mes("hook set ");
    _ropeHook->resetCurrentState();
    mes+=QString::number(value);
    _ropeHook->increment(value);
    addText(mes);
}

void CraneWidget::on__verticalSliderTelescopic_valueChanged(int value)
{
    QString mes("telescopic set ");
    _telescopic->resetCurrentState();
    _telescopicTop->resetCurrentState();
    mes+=QString::number(value);
    _telescopic->increment(value);
    _telescopicTop->increment(value);
    addText(mes);
}

void CraneWidget::on__verticalSliderOutrigger_valueChanged(int value)
{
    QString mes("outrigger set ");
    _outrigger->resetCurrentState();
    _outriggerTop->resetCurrentState();
    int v = ui->_verticalSliderOutrigger->maximum() - value;
    mes+=QString::number(v);
    _outrigger->decrement(v);
    _outriggerTop->decrement(v);
    addText(mes);
}

void CraneWidget::on__verticalSliderDerrick_valueChanged(int value)
{
    QString mes("derrick set ");
    _derrick->resetCurrentState();
    _derrickTop->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _derrick->increment(v);
    _derrickTop->increment(v);
    addText(mes);
}

void CraneWidget::on__verticalSliderPillar_valueChanged(int value)
{
    QString mes("pillar set ");
    _pillar->resetCurrentState();
    _pillarTop->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    if(v>=0)
    {
        _pillar->increment(v);
        _pillarTop->increment(v);
    }
    else
    {
        _pillar->decrement(qAbs(v));
        _pillarTop->decrement(qAbs(v));
    }
    addText(mes);
}

void CraneWidget::on__verticalSliderRightCrutch_valueChanged(int value)
{
    QString mes("right crutch set ");
    _rightCrutch->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _rightCrutch->increment(v);
    addText(mes);
}

void CraneWidget::on__verticalSliderLeftCrutch_valueChanged(int value)
{
    QString mes("left crutch set ");
    _leftCrutch->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _leftCrutch->increment(v);
    addText(mes);
}

void CraneWidget::on__pushButtonDebug_clicked()
{
    if(_lightOn->isVisible())
    {
        _lightOn->setVisible(false);
        _lightOnTop->setVisible(false);
    }
    else
    {
        _lightOn->setVisible(true);
        _lightOnTop->setVisible(true);
    }
}


void CraneWidget::on__pushButtonPower_clicked(bool checked)
{
    if(checked)
    {
        ui->_pushButtonPower->setText("Power On");
        emit signalPowerOn();
    }
    else
    {
        ui->_pushButtonPower->setText("Power Off");
        emit signalPowerOff();
    }
}

void CraneWidget::on__pushButtonLight_clicked(bool checked)
{
    if(checked)
    {
        ui->_pushButtonLight->setText("Light On");
        _lightOn->setVisible(true);
        _lightOnTop->setVisible(true);
        emit signalLightOn();
    }
    else
    {
        ui->_pushButtonLight->setText("Light Off");
        _lightOn->setVisible(false);
        _lightOnTop->setVisible(false);
        emit signalLightOff();
    }
}

void CraneWidget::on__pushButtonTemperatureWarning_clicked(bool checked)
{
    if(checked)
    {
        ui->_pushButtonTemperatureWarning->setText("Temperature Warning on");
        ui->_pushButtonTemperatureWarning->setStyleSheet("color: red;  font-weight: bold");
        emit temperatureHigh();
    }
    else
    {
        ui->_pushButtonTemperatureWarning->setText("Temperature Warning off");
        ui->_pushButtonTemperatureWarning->setStyleSheet("color: black;  font-weight: normal");
        emit temperatureNormal();
    }
}

void CraneWidget::on__pushButtonSoundSignal_pressed()
{
    soundSignalOn(true);
}

void CraneWidget::on__pushButtonSoundSignal_released()
{
    soundSignalOn(false);
}
