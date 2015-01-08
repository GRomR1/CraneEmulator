#include "LeftCrutchItem.h"

LeftCrutchItem::LeftCrutchItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=LeftCrutch;
    setId("left_crutch");
}

void LeftCrutchItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(0,_currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Increment, _currentState);
}

void LeftCrutchItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(0,_currentState);
    setTransform(trans);

    emit itemIsChanged(_type, Decrement, _currentState);
}

void LeftCrutchItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

void LeftCrutchItem::resetCurrentState()
{
    AbstractItem::resetCurrentState();
    resetTransform();
}

qreal LeftCrutchItem::min() const
{
    return minY();
}

qreal LeftCrutchItem::max() const
{
   return maxY();
}
