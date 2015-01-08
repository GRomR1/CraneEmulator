#include "AbstractItem.h"

AbstractItem::AbstractItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    QGraphicsSvgItem(parent),
    _minAngle(DefaultMinAngle),
    _maxAngle(DefaultMaxAngle),
    _pointMin(QPointF(0,0)),
    _pointMax(QPointF(0,0)),
    _countSteps(DefaultCountSteps),
    _currentState(0)
{
    _renderer = renderer;
    setSharedRenderer(_renderer);
    _type = Abstract;
}


void AbstractItem::setId(QString id)
{
    setElementId(id);
    setPos(_renderer->boundsOnElement(id).topLeft());
//    _basicPos = pos();
}

int AbstractItem::type() const
{
    return _type;
}

void AbstractItem::resetCurrentState()
{
    _currentState=0;
}

//QPointF AbstractItem::basicPos()
//{
//    return _basicPos;
//}


void AbstractItem::slotItemChanged(GraphicsItemChange change)
{
    emit signalItemChanged(change);
}


void AbstractItem::increment(int value)
{
    if(value < 0)
    {
        decrement(qAbs(value));
        return;
    }
    for(int i=0; i<value; i++)
        increment();
}

void AbstractItem::decrement(int value)
{
    if(value < 0)
    {
        increment(qAbs(value));
        return;
    }
    for(int i=0; i<value; i++)
        decrement();
}

int AbstractItem::countSteps() const
{
    return _countSteps;
}

qreal AbstractItem::currentStep() const
{
    return _currentStep;
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
