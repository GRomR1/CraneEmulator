#include "PillarItem.h"

PillarItem::PillarItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Pillar;
    setId("pillar");
}

void PillarItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
    _currentState = newState;
    emit itemIsChanged(_type, Increment, _currentState);
}

void PillarItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
    _currentState = newState;
    emit itemIsChanged(_type, Decrement, _currentState);
}

void PillarItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}


qreal PillarItem::min() const
{
    return minAngle();
}

qreal PillarItem::max() const
{
    return maxAngle();
}
