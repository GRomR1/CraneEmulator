#include "OutriggerItem.h"

OutriggerItem::OutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Outrigger;
    setId("outrigger");
}

QVariant OutriggerItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    emit signalItemChanged(change);
    return AbstractItem::itemChange(change, value);
}

void OutriggerItem::resetCurrentState()
{
    AbstractItem::resetCurrentState();
    resetTransform();
}

void OutriggerItem::increment()
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

void OutriggerItem::decrement()
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

void OutriggerItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

qreal OutriggerItem::min() const
{
    return maxAngle();
}

qreal OutriggerItem::max() const
{
   return minAngle();
}
