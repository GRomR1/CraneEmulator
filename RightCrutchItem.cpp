#include "RightCrutchItem.h"

RightCrutchItem::RightCrutchItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=RightCrutch;
    setId("right_crutch");
}

void RightCrutchItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(0, _currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Increment, _currentState);
}

void RightCrutchItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(0, _currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Decrement, _currentState);
}

void RightCrutchItem::resetCurrentState()
{
    AbstractItem::resetCurrentState();
    resetTransform();
}

qreal RightCrutchItem::min() const
{
    return minY();
}

qreal RightCrutchItem::max() const
{
   return maxY();
}
