#include "AbstractItem.h"

AbstractItem::AbstractItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    QGraphicsSvgItem(parent),
    _parentScaleXValue(1),
    _parentScaleYValue(1),
    _parentRotateValue(0),
    _parentTranslateXValue(0),
    _parentTranslateYValue(0),
    _minAngle(DefaultMinAngle),
    _maxAngle(DefaultMaxAngle),
    _pointMin(QPointF(0,0)),
    _pointMax(QPointF(0,0)),
    _minScale(1),
    _maxScale(1),
    _countSteps(DefaultCountSteps),
    _currentState(0)
{
    _renderer = renderer;
    setSharedRenderer(_renderer);
    _type = Abstract;
    setCacheMode(QGraphicsItem::NoCache);
}


void AbstractItem::setId(QString id)
{
    setElementId(id);
    setPos(_renderer->boundsOnElement(id).topLeft());
}

int AbstractItem::type() const
{
    return _type;
}

void AbstractItem::resetCurrentState()
{
}

QPointF AbstractItem::basicPos()
{
    return _basicPos;
}

void AbstractItem::setBasicPos(QPointF p)
{
//    qDebug()<<pos() << p;
    _basicPos=p;
}

void AbstractItem::setParentItemMy(AbstractItem *item)
{
    _parentItem = item;
    connect(_parentItem, SIGNAL(scaleXChanged(qreal)),
            this, SLOT(parentScaleXChanged(qreal)));
    connect(_parentItem, SIGNAL(scaleYChanged(qreal)),
            this, SLOT(parentScaleYChanged(qreal)));

    connect(_parentItem, SIGNAL(rotationChanged(qreal)),
            this, SLOT(parentRotationChanged(qreal)));

    connect(_parentItem, SIGNAL(translateXChanged(qreal)),
            this, SLOT(parentTranslateXChanged(qreal)));
    connect(_parentItem, SIGNAL(translateYChanged(qreal)),
            this, SLOT(parentTranslateYChanged(qreal)));

    setBasicPos(_parentItem->mapFromScene(pos()));
}

void AbstractItem::setValue(qreal v)
{
    if(v > min() && v < max())
        _currentState = v;
}

qreal AbstractItem::value() const
{
    return _currentState;
}

int AbstractItem::countSteps() const
{
    return _countSteps;
}

qreal AbstractItem::currentStep() const
{
    return _currentStep;
}
qreal AbstractItem::currentState() const
{
    return _currentState;
}
void AbstractItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

qreal AbstractItem::minAngle() const
{
    return _minAngle;
}

qreal AbstractItem::maxAngle() const
{
    return _maxAngle;
}

void AbstractItem::setMinAngle(qreal angle)
{
    if(qAbs(angle) >= 180)
        _maxAngle = 180.;
    else
        _maxAngle = qAbs(angle);
}

void AbstractItem::setMaxAngle(qreal angle)
{
    if(qAbs(angle) >= 180)
        _minAngle = -180.;
    else
        _minAngle = 0 - qAbs(angle);
}


qreal AbstractItem::minX() const
{
    return _pointMin.x();
}

qreal AbstractItem::minY() const
{
    return _pointMin.y();
}

qreal AbstractItem::maxX() const
{
    return _pointMax.x();
}
qreal AbstractItem::maxY() const
{
    return _pointMax.y();
}

void AbstractItem::setMaxX(qreal v)
{
    _pointMax.setX(v);
}

void AbstractItem::setMaxY(qreal v)
{
    _pointMax.setY(v);
}

void AbstractItem::setMinX(qreal v)
{
    _pointMin.setX(v);
}

void AbstractItem::setMinY(qreal v)
{
    _pointMin.setY(v);
}

qreal AbstractItem::minScale() const
{
    return _minScale;
}

qreal AbstractItem::maxScale() const
{
    return _maxScale;
}

void AbstractItem::setMinScale(qreal v)
{
    _minScale=v;
}

void AbstractItem::setMaxScale(qreal v)
{
    _maxScale=v;
}
