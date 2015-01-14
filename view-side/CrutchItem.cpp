#include "CrutchItem.h"

using namespace Side;

CrutchItem::CrutchItem(int type, QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    if((TypeItem)type == LeftCrutch)
    {
        _type=LeftCrutch;
        setId("left_crutch");
    }
    else if((TypeItem)type == RightCrutch)
    {
        _type=RightCrutch;
        setId("right_crutch");
    }
}

void CrutchItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void CrutchItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}

void CrutchItem::increment(int value)
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
        newState += _currentStep;
        if(newState > max())
            newState = max();
    }
    compareAndSetState(newState);
}

void CrutchItem::decrement(int value)
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
        newState -= _currentStep;
        if(newState < min())
            newState = min();
    }
    compareAndSetState(newState);
}

void CrutchItem::resetCurrentState()
{
    compareAndSetState(0);
}

qreal CrutchItem::min() const
{
    return minY();
}

qreal CrutchItem::max() const
{
   return maxY();
}
void CrutchItem::setMin(qreal v)
{
    setMinY(v);
}
void CrutchItem::setMax(qreal v)
{
    setMaxY(v);
}

void CrutchItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        QTransform trans;
        trans.translate(0,_currentState);
        setTransform(trans);
//        emit itemIsChanged(_type, Increment, _currentState);
        emit translateYChanged(_currentState);
    }
}
