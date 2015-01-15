#include "Side_PillarItem.h"

using namespace Side;

PillarItem::PillarItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Pillar;
    setId("pillar");
}

void PillarItem::resetCurrentState()
{
    compareAndSetState(0);
}

void PillarItem::increment()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}

void PillarItem::decrement()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void PillarItem::increment(int value)//поворот стойки по часовой стрелке на value шагов
{
    if(value < 0)
    {
        decrement(qAbs(value));
        return;
    }
    if(!value)
        return;
    qreal newState = _currentState;
    for(int i=0; i<value; i++)
    {
        newState -= _currentStep;
        if(newState < min())
            newState = min();
    }
    compareAndSetState(newState);
}

void PillarItem::decrement(int value)//поворот стойки против часовой стрелке на value шагов
{
    if(value < 0)
    {
        increment(qAbs(value));
        return;
    }
    if(!value)
        return;
    qreal newState = _currentState;
    for(int i=0; i<value; i++)
    {
        newState += _currentStep;
        if(newState > max())
            newState = max();
    }
    compareAndSetState(newState);
}

qreal PillarItem::min() const
{
    return minAngle();
}

qreal PillarItem::max() const
{
    return maxAngle();
}
void PillarItem::setMin(qreal v)
{
    setMinAngle(v);
}
void PillarItem::setMax(qreal v)
{
    setMaxAngle(v);
}

void PillarItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
//        emit itemIsChanged(_type, Increment, _currentState);
        qreal cosValue = cos((double)_currentState*M_PI/180.);
        emit scaleXChanged(cosValue);
    }
}
