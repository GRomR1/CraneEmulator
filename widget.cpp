#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    _itemEllipseForDebug(0)
{
    ui->setupUi(this);
    _scene = new GraphicsScene(QRectF(0, 30, 220, 150));
    _sceneTop = new GraphicsScene(QRectF(0, 0, 220, 120));
    QSvgRenderer *renderer = new QSvgRenderer(QString(":/Кран_ВидCбоку.svg"));
//    QSvgRenderer *rendererTop = new QSvgRenderer(QString(":/Кран_ВидСверху.svg"));
    QGraphicsSvgItem *item1Top = new QGraphicsSvgItem(QString(":/Кран_ВидСверху.svg"));
    _sceneTop->addItem(item1Top);
//    qDebug() << renderer->elementExists("pillar") << renderer->elementExists("hook") << "";
//    qDebug() << renderer->boundsOnElement("pillar").topLeft() << renderer->boundsOnElement("hook").topLeft();

    _leftCrutch = new Side::CrutchItem(AbstractItems::LeftCrutch, renderer);
    _leftCrutch->setMax(10);
    _leftCrutch->setCountSteps(5);
    ui->_verticalSliderLeftCrutch->setMaximum(5);
    ui->_verticalSliderLeftCrutch->setSingleStep(1);

    _rightCrutch = new Side::CrutchItem(AbstractItems::RightCrutch, renderer);
    _rightCrutch->setMax(10);
    _rightCrutch->setCountSteps(5);
    ui->_verticalSliderRightCrutch->setMaximum(5);
    ui->_verticalSliderRightCrutch->setSingleStep(1);

    _pillar = new Side::PillarItem(renderer);
    _pillar->setMax(50);
    _pillar->setMin(-50);
    _pillar->setCountSteps(10);
    ui->_verticalSliderPillar->setMaximum(5);
    ui->_verticalSliderPillar->setMinimum(-5);
    ui->_verticalSliderPillar->setSingleStep(1);
    ui->_verticalSliderPillar->setValue(0);

    _ellipseDerrick = new Side::OtherItem(AbstractItems::EllipseDerick, renderer);
    _ellipseDerrick->setId("ellipse_derrick");

    _derrick = new Side::DerrickItem(renderer);
    _derrick->setFlags(QGraphicsItem::ItemStacksBehindParent /*|
                        QGraphicsItem::ItemSendsGeometryChanges*/);
    _derrick->setMax(30);
    _derrick->setMin(0);
    _derrick->setCountSteps(15);
    _derrick->setParentItemMy(_pillar);
    ui->_verticalSliderDerrick->setMaximum(15);
    ui->_verticalSliderDerrick->setSingleStep(1);

    _ellipseOutrigger = new Side::EllipseOutriggerItem(renderer);
    _ellipseOutrigger->setParentItemMy(_derrick);
    _scene->addItem(_ellipseOutrigger);

    _outrigger = new Side::OutriggerItem(renderer);
    _outrigger->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _outrigger->setMax(0);
    _outrigger->setMin(-30);
    _outrigger->setCountSteps(15);
    ui->_verticalSliderOutrigger->setMaximum(15);
    ui->_verticalSliderOutrigger->setValue(15);
    ui->_verticalSliderOutrigger->setSingleStep(1);
    _outrigger->setParentItemMy(_ellipseOutrigger);

    _telescopic = new Side::TelescopicItem(renderer);
    _telescopic->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _telescopic->setMax(20);
    _telescopic->setMin(0);
    _telescopic->setCountSteps(10);
    ui->_verticalSliderTelescopic->setMaximum(10);
    ui->_verticalSliderTelescopic->setValue(0);
    ui->_verticalSliderTelescopic->setSingleStep(1);
    _telescopic->setParentItemMy(_outrigger);

    _ellipseHook = new Side::EllipseHookItem(renderer);
    _ellipseHook->setParentItemMy(_telescopic);
//    connect(_ellipseHook, SIGNAL(needDrawPoint(QPointF)),
//            this, SLOT(drawPoint(QPointF)));

    _ropeHook = new Side::RopeHookItem(renderer);
//    _ropeHook->setFlags(QGraphicsItem::ItemStacksBehindParent |
//                        QGraphicsItem::ItemSendsGeometryChanges);
    _ropeHook->setParentItemMy(_ellipseHook);
    _ropeHook->setMax(51);
    _ropeHook->setMin(1);
    _ropeHook->setCountSteps(20);
    _ropeHook->setValue(1.1);
    ui->_verticalSliderRopeHook->setMaximum(20);
    ui->_verticalSliderRopeHook->setSingleStep(1);
    connect(_ropeHook, SIGNAL(minIsReached()),
            this, SLOT(showHookWarning()));
    connect(_ropeHook, SIGNAL(stopMinIsReached()),
            this, SLOT(stopHookWarning()));

    _hook = new Side::HookItem(renderer);
    _hook->setParentItemMy(_ropeHook);

    _ground = new Side::OtherItem(AbstractItems::Ground, renderer);
    _ground->setId("ground");

    _scene->addItem(_leftCrutch);
    _scene->addItem(_rightCrutch);
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

    _sceneTop->setSceneRect(item1Top->boundingRect());
    _sceneTop->addRect(item1Top->boundingRect(), QPen(Qt::green));
    ui->_viewTop->setScene(_sceneTop);

//    _scene->addLine(QLineF(0, 0, 300, 0), QPen(Qt::green, 0.5)); //horizontal (y1==y2)
//    _scene->addLine(QLineF(0, 0, 0, 200), QPen(Qt::green, 0.5)); //vertical (x1==x2)

    QPointF p(0,0);
    _itemEllipse = _scene->addEllipse(QRectF(p.x(),p.y(),1,1), QPen(Qt::NoPen), QBrush(Qt::red));
    connect(_scene, SIGNAL(clicked(QPointF)),
            this, SLOT(sceneClicked(QPointF)));

    ui->_verticalSliderScale->setValue(25);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::addText(QString txt)
{
    ui->_ptEdit->appendPlainText(txt);
    ui->_ptEdit->centerCursor();
}


void Widget::sceneClicked(QPointF point)
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

//    qDebug() << _derrick->transformOriginPoint();
//    _derrick->setTransformOriginPoint(_derrick->mapFromScene(point));

    addText(str);
}

void Widget::drawPoint(QPointF p)
{
    if(_itemEllipseForDebug)
    {
        _scene->removeItem(_itemEllipseForDebug);
        delete _itemEllipseForDebug;
        _itemEllipseForDebug=0;
    }

    _itemEllipseForDebug = _scene->addEllipse(QRectF(p.x(),p.y(),1,1), QPen(Qt::NoPen), QBrush(Qt::green));
}

void Widget::showHookWarning()
{
    ui->_pushButtonHookWarning->setStyleSheet("color: red;  font-weight: bold");
}

void Widget::stopHookWarning()
{
    ui->_pushButtonHookWarning->setStyleSheet("color: black;  font-weight: normal");
}

void Widget::showTemperatureWarning()
{
    ui->_pushButtonTemperatureWarning->setStyleSheet("color: red;  font-weight: bold");
}

void Widget::stopTemperatureWarning()
{
    ui->_pushButtonTemperatureWarning->setStyleSheet("color: black;  font-weight: normal");
}

void Widget::on__pushButtonDerrickRotatePlus_clicked()
{
    QString mes("derrick +");
//    _derrick->increment();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() +
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void Widget::on__pushButtonDerrickRotateMinus_clicked()
{
    QString mes("derrick -");
//    _derrick->decrement();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() -
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void Widget::on__pushButtonOutriggerRotatePlus_clicked()
{
    QString mes("outrigger +");
//    _outrigger->increment();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() +
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void Widget::on__pushButtonOutriggerRotateMinus_clicked()
{
    QString mes("outrigger -");
//    _outrigger->decrement();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() -
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRopeHookPlus_clicked()
{
    QString mes("rope hook +");
    ui->_verticalSliderRopeHook->setValue(
                ui->_verticalSliderRopeHook->value() +
                ui->_verticalSliderRopeHook->singleStep());
//    _ropeHook->increment();
    addText(mes);
}


void Widget::on__pushButtonRopeHookMinus_clicked()
{
    QString mes("rope hook -");
    ui->_verticalSliderRopeHook->setValue(
                ui->_verticalSliderRopeHook->value() -
                ui->_verticalSliderRopeHook->singleStep());
//    _ropeHook->decrement();
    addText(mes);
}
void Widget::on__pushButtonTelescopicPlus_clicked()
{
    QString mes("telescopic +");
//    _telescopic->increment();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() +
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void Widget::on__pushButtonTelescopicMinus_clicked()
{
    QString mes("telescopic -");
//    _telescopic->decrement();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() -
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void Widget::on__pushButtonLeftCrutchPlus_clicked()
{
    QString mes("left crutch +");
//    _leftCrutch->increment();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() +
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonLeftCrutchMinus_clicked()
{
    QString mes("left crutch -");
//    _leftCrutch->decrement();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() -
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRightCrutchPlus_clicked()
{
    QString mes("right crutch +");
//    _rightCrutch->increment();
    ui->_verticalSliderRightCrutch->setValue(
                ui->_verticalSliderRightCrutch->value() +
                ui->_verticalSliderRightCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRightCrutchMinus_clicked()
{
    QString mes("right crutch -");
//    _rightCrutch->decrement();
    ui->_verticalSliderRightCrutch->setValue(
                ui->_verticalSliderRightCrutch->value() -
                ui->_verticalSliderRightCrutch->singleStep());
    addText(mes);
}

void Widget::on__verticalSliderScale_valueChanged(int value)
{
    ui->_view->resetTransform();
    ui->_view->scale(value*1.0/10,value*1.0/10);
}

//void Widget::on__verticalSliderLeftCrutch_sliderReleased()
//{
//    QString mes("left crutch set ");
//    _leftCrutch->resetCurrentState();
//    int v = ui->_verticalSliderLeftCrutch->value();
//    mes+=QString::number(v);
//    _leftCrutch->increment(v);
//    addText(mes);
//}

//void Widget::on__verticalSliderRightCrutch_sliderReleased()
//{
//    QString mes("right crutch set ");
//    _rightCrutch->resetCurrentState();
//    int v = ui->_verticalSliderRightCrutch->value();
//    mes+=QString::number(v);
//    _rightCrutch->increment(v);
//    addText(mes);
//}

//void Widget::on__verticalSliderDerrick_sliderReleased()
//{
//    QString mes("derrick set ");
//    _derrick->resetCurrentState();
//    int v = ui->_verticalSliderDerrick->value();
//    mes+=QString::number(v);
//    if(v==0)
//        _derrick->resetCurrentState();
//    else
//        _derrick->increment(v);
//    addText(mes);
//}

//void Widget::on__verticalSliderOutrigger_sliderReleased()
//{
//    QString mes("outrigger set ");
//    _outrigger->resetCurrentState();
//    int v = ui->_verticalSliderOutrigger->maximum() - ui->_verticalSliderOutrigger->value();
//    mes+=QString::number(v);
//    _outrigger->decrement(v);
//    addText(mes);
//}

void Widget::on__pushButtonPillarPlus_clicked()
{
    QString mes("pillar +");
    ui->_verticalSliderPillar->setValue(
                ui->_verticalSliderPillar->value() +
                ui->_verticalSliderPillar->singleStep());
//    _pillar->increment();
    addText(mes);
}

void Widget::on__pushButtonPillarMinus_clicked()
{
    QString mes("pillar -");
    ui->_verticalSliderPillar->setValue(
                ui->_verticalSliderPillar->value() -
                ui->_verticalSliderPillar->singleStep());
//    _pillar->decrement();
    addText(mes);
}


void Widget::on__pushButtonSetTemperatureWarning_clicked(bool checked)
{
    if(checked)
    {
        ui->_pushButtonSetTemperatureWarning->setText("Unset");
        showTemperatureWarning();
    }
    else
    {
        ui->_pushButtonSetTemperatureWarning->setText("Set");
        stopTemperatureWarning();
    }
}

void Widget::on__verticalSliderRopeHook_valueChanged(int value)
{
    QString mes("hook set ");
    _ropeHook->resetCurrentState();
    mes+=QString::number(value);
    _ropeHook->increment(value);
    addText(mes);
}

void Widget::on__verticalSliderTelescopic_valueChanged(int value)
{
    QString mes("telescopic set ");
    _telescopic->resetCurrentState();
    mes+=QString::number(value);
    _telescopic->increment(value);
    addText(mes);
}

void Widget::on__verticalSliderOutrigger_valueChanged(int value)
{
    QString mes("outrigger set ");
    _outrigger->resetCurrentState();
    int v = ui->_verticalSliderOutrigger->maximum() - value;
    mes+=QString::number(v);
    _outrigger->decrement(v);
    addText(mes);
}

void Widget::on__verticalSliderDerrick_valueChanged(int value)
{
    QString mes("derrick set ");
    _derrick->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _derrick->increment(v);
    addText(mes);
}

void Widget::on__verticalSliderPillar_valueChanged(int value)
{
    QString mes("pillar set ");
    _pillar->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    if(v>=0)
        _pillar->increment(v);
    else
        _pillar->decrement(qAbs(v));
    addText(mes);
}

void Widget::on__verticalSliderRightCrutch_valueChanged(int value)
{
    QString mes("right crutch set ");
    _rightCrutch->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _rightCrutch->increment(v);
    addText(mes);
}

void Widget::on__verticalSliderLeftCrutch_valueChanged(int value)
{
    QString mes("left crutch set ");
    _leftCrutch->resetCurrentState();
    int v = value;
    mes+=QString::number(v);
    _leftCrutch->increment(v);
    addText(mes);
}
