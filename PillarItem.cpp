#include "PillarItem.h"

PillarItem::PillarItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Pillar;
    setId("pillar");
}

void PillarItem::resetCurrentState()
{
//    AbstractItem::resetCurrentState();
//    resetTransform();
//    qDebug() << "reset";
//    emit itemIsChanged(_type, Reset, _currentState);
//    emit scaledChanged(1);
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
//        AbstractItem::decrement(value);
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


void PillarItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        // Значения не равны
        _currentState = newState;
//        emit itemIsChanged(_type, Increment, _currentState);
        qreal cosValue = cos((double)_currentState*M_PI/180.);
        emit scaledChanged(cosValue);
    }
}
