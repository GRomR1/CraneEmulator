#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    _scene = new GraphicsScene(QRectF(0, 0, 300, 200));
    ui->_view->setScene(_scene);
    QSvgRenderer *renderer = new QSvgRenderer(QString(":/Кран_ВидCбоку.svg"));
//    qDebug() << renderer->elementExists("pillar") << renderer->elementExists("hook") << "";
//    qDebug() << renderer->boundsOnElement("pillar").topLeft() << renderer->boundsOnElement("hook").topLeft();

    _leftCrutch = new LeftCrutchItem(renderer);
    _leftCrutch->setMax(10);
    _leftCrutch->setCountSteps(5);
    ui->_verticalSliderLeftCrutch->setMaximum(5);
    ui->_verticalSliderLeftCrutch->setSingleStep(1);

    _rightCrutch = new RightCrutchItem(renderer);
    _rightCrutch->setMax(10);
    _rightCrutch->setCountSteps(5);
    ui->_verticalSliderRightCrutch->setMaximum(5);
    ui->_verticalSliderRightCrutch->setSingleStep(1);

    _pillar = new PillarItem(renderer);

    _derrick = new DerrickItem(renderer);
    _derrick->setFlags(QGraphicsItem::ItemStacksBehindParent /*|
                        QGraphicsItem::ItemSendsGeometryChanges*/);
    _derrick->setMax(30);
    _derrick->setMin(0);
    _derrick->setCountSteps(15);
    ui->_verticalSliderDerrick->setMaximum(15);
    ui->_verticalSliderDerrick->setSingleStep(1);

    _ellipseDerrick = new OtherItem(AbstractItems::EllipseDerick, renderer);
    _ellipseDerrick->setId("ellipse_derrick");

    _ellipseOutrigger = new OtherItem(AbstractItems::EllipseOutrigger, renderer);
    _ellipseOutrigger->setId("ellipse_outrigger");
    _ellipseOutrigger->setPos(_ellipseOutrigger->mapToItem(_derrick, QPointF(0,0)));
    _ellipseOutrigger->setParentItem(_derrick);

    _outrigger = new OutriggerItem(renderer);
    _outrigger->setPos(_outrigger->mapToItem(_derrick, QPointF(0,0)));
    _outrigger->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _outrigger->setParentItem(_derrick);
    _outrigger->setMax(0);
    _outrigger->setMin(-30);
    _outrigger->setCountSteps(15);
    ui->_verticalSliderOutrigger->setMaximum(15);
    ui->_verticalSliderOutrigger->setValue(15);
    ui->_verticalSliderOutrigger->setSingleStep(1);

    _telescopic = new TelescopicItem(renderer);
    _telescopic->setPos(_telescopic->mapToItem(_outrigger, QPointF(0,0)));
    _telescopic->setFlags(QGraphicsItem::ItemStacksBehindParent);
    _telescopic->setParentItem(_outrigger);
    _telescopic->setMax(20);
    _telescopic->setMin(0);
    _telescopic->setCountSteps(10);
    ui->_verticalSliderTelescopic->setMaximum(10);
    ui->_verticalSliderTelescopic->setValue(0);
    ui->_verticalSliderTelescopic->setSingleStep(1);

    _ellipseHook = new OtherItem(AbstractItems::EllipseHook, renderer);
    _ellipseHook->setId("ellipse_hook");
    _ellipseHook->setPos(_ellipseHook->mapToItem(_telescopic, QPointF(0,0)));
    _ellipseHook->setParentItem(_telescopic);

    _ropeHook = new RopeHookItem(renderer);
    _ropeHook->setId("rope_hook");
    _ropeHook->setPos(_ropeHook->mapToItem(_telescopic, QPointF(0,0)));
    _ropeHook->setFlags(QGraphicsItem::ItemStacksBehindParent |
                        QGraphicsItem::ItemSendsGeometryChanges);
    _ropeHook->setParentItem(_telescopic);

    _hook = new HookItem(renderer);
    _hook->setId("hook");
    _hook->setPos(_hook->mapToItem(_ropeHook, QPointF(0,0)));
    _hook->setFlags(QGraphicsItem::ItemStacksBehindParent |
                    QGraphicsItem::ItemSendsGeometryChanges);
    _hook->setParentItem(_ropeHook);

    _ground = new OtherItem(AbstractItems::Ground, renderer);
    _ground->setId("ground");


    _scene->addItem(_ground);
    _scene->addItem(_leftCrutch);
    _scene->addItem(_rightCrutch);
//    _scene->addItem(_ropeHook);
//    _scene->addItem(_hook);
//    _scene->addItem(_telescopic);
//    _scene->addItem(_outrigger);
    _scene->addItem(_derrick);
    _scene->addItem(_pillar);
    _scene->addItem(_ellipseDerrick);

//    _scene->addItem(_ellipseOutrigger);

//    connect(_derrick, SIGNAL(signalItemChanged(GraphicsItemChange)),
//            _outrigger, SLOT(slotItemChanged(GraphicsItemChange)));
//    connect(_outrigger, SIGNAL(signalItemChanged(GraphicsItemChange)),
//            _telescopic, SLOT(slotItemChanged(GraphicsItemChange)));
//    connect(_telescopic, SIGNAL(signalItemChanged(GraphicsItemChange)),
//            _ropeHook, SLOT(slotItemChanged(GraphicsItemChange)));

//    connect(_ropeHook, SIGNAL(signalItemChanged(GraphicsItemChange)),
//            _hook, SLOT(slotItemChanged(GraphicsItemChange)));

//    connect(_telescopic, SIGNAL(rotationChanged()),
//            _ropeHook, SLOT(slotRotationChanged()));
//    connect(_outrigger, SIGNAL(rotationChanged()),
//            _ropeHook, SLOT(slotRotationChanged()));
//    connect(_derrick, SIGNAL(rotationChanged()),
//            _ropeHook, SLOT(slotRotationChanged()));

//    _scene->addLine(QLineF(0, 0, 300, 0), QPen(Qt::green, 0.5)); //horizontal (y1==y2)
//    _scene->addLine(QLineF(0, 0, 0, 200), QPen(Qt::green, 0.5)); //vertical (x1==x2)
    _itemEllipse = _scene->addEllipse(QRectF(0,0,1,1), QPen(Qt::NoPen), QBrush(Qt::red));
    connect(_scene, SIGNAL(clicked(QPointF)),
            this, SLOT(sceneClicked(QPointF)));


    ui->_view->scale(4,4);
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


void Widget::on__pushButtonDerrickRotatePlus_clicked()
{
    QString mes("derrick +");
    _derrick->increment();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() +
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void Widget::on__pushButtonDerrickRotateMinus_clicked()
{
    QString mes("derrick -");
    _derrick->decrement();
    ui->_verticalSliderDerrick->setValue(
                ui->_verticalSliderDerrick->value() -
                ui->_verticalSliderDerrick->singleStep());
    addText(mes);
}

void Widget::on__pushButtonOutriggerRotatePlus_clicked()
{
    QString mes("outrigger +");
    _outrigger->increment();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() +
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void Widget::on__pushButtonOutriggerRotateMinus_clicked()
{
    QString mes("outrigger -");
    _outrigger->decrement();
    ui->_verticalSliderOutrigger->setValue(
                ui->_verticalSliderOutrigger->value() -
                ui->_verticalSliderOutrigger->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRopeHookPlus_clicked()
{
    QString mes("rope length ");
    QTransform trans = _ropeHook->transform();
//    trans.m22();
    trans.scale(1, 1.1);
    _ropeHook->setTransform(trans);
    mes+="+";
    addText(mes);
}


void Widget::on__pushButtonRopeHookMinus_clicked()
{
    QString mes("rope length ");
    QTransform trans = _ropeHook->transform();
    trans.scale(1, 0.75);
    _ropeHook->setTransform(trans);
    mes+="-";
    addText(mes);
}

void Widget::on__pushButtonTelescopicPlus_clicked()
{
    QString mes("telescopic +");
    _telescopic->increment();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() +
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void Widget::on__pushButtonTelescopicMinus_clicked()
{
    QString mes("telescopic +");
    _telescopic->decrement();
    ui->_verticalSliderTelescopic->setValue(
                ui->_verticalSliderTelescopic->value() -
                ui->_verticalSliderTelescopic->singleStep());
    addText(mes);
}

void Widget::on__pushButtonLeftCrutchPlus_clicked()
{
    QString mes("left crutch +");
    _leftCrutch->increment();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() +
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonLeftCrutchMinus_clicked()
{
    QString mes("left crutch -");
    _leftCrutch->decrement();
    ui->_verticalSliderLeftCrutch->setValue(
                ui->_verticalSliderLeftCrutch->value() -
                ui->_verticalSliderLeftCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRightCrutchPlus_clicked()
{
    QString mes("right crutch +");
    _rightCrutch->increment();
    ui->_verticalSliderRightCrutch->setValue(
                ui->_verticalSliderRightCrutch->value() +
                ui->_verticalSliderRightCrutch->singleStep());
    addText(mes);
}

void Widget::on__pushButtonRightCrutchMinus_clicked()
{
    QString mes("right crutch -");
    _rightCrutch->decrement();
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

void Widget::on__verticalSliderLeftCrutch_sliderReleased()
{
    QString mes("left crutch set ");
    _leftCrutch->resetCurrentState();
    int v = ui->_verticalSliderLeftCrutch->value();
    mes+=QString::number(v);
    _leftCrutch->increment(v);
    addText(mes);
}

void Widget::on__verticalSliderRightCrutch_sliderReleased()
{
    QString mes("right crutch set ");
    _rightCrutch->resetCurrentState();
    int v = ui->_verticalSliderRightCrutch->value();
    mes+=QString::number(v);
    _rightCrutch->increment(v);
    addText(mes);
}

void Widget::on__verticalSliderDerrick_sliderReleased()
{
    QString mes("derrick set ");
    _derrick->resetCurrentState();
    int v = ui->_verticalSliderDerrick->value();
    mes+=QString::number(v);
    _derrick->increment(v);
    addText(mes);
}

void Widget::on__verticalSliderOutrigger_sliderReleased()
{
    QString mes("outrigger set ");
    _outrigger->resetCurrentState();
    int v = ui->_verticalSliderOutrigger->maximum() - ui->_verticalSliderOutrigger->value();
    mes+=QString::number(v);
    _outrigger->decrement(v);
    addText(mes);
}

void Widget::on__verticalSliderTelescopic_sliderReleased()
{
    QString mes("telescopic set ");
    _telescopic->resetCurrentState();
    int v = ui->_verticalSliderTelescopic->value();
    mes+=QString::number(v);
    _telescopic->increment(v);
    addText(mes);
}
