#include "DerrickItem.h"

DerrickItem::DerrickItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Derrick;
    setId("derrick");

    QPointF p(0, boundingRect().height()/2);
    setTransformOriginPoint(p);
}

QVariant DerrickItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    emit signalItemChanged(change);
    return AbstractItem::itemChange(change, value);
}

void DerrickItem::increment()
{
    qreal newState = _currentState - _currentStep;
    if(newState < max())
        newState = max();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.rotate(_currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Increment, _currentState);
}

void DerrickItem::decrement()
{
    qreal newState = _currentState + _currentStep;
    if(newState > min())
        newState = min();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.rotate(_currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Decrement, _currentState);
}

void DerrickItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

void DerrickItem::resetCurrentState()
{
    AbstractItem::resetCurrentState();
    resetTransform();
}

qreal DerrickItem::min() const
{
    return maxAngle();
}

qreal DerrickItem::max() const
{
   return minAngle();
}
