#include "RopeHookItem.h"

using namespace Side;

RopeHookItem::RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = RopeHook;
    _minIsReached=false;

    setId("rope_hook");
}

void RopeHookItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void RopeHookItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}
void RopeHookItem::increment(int value)
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

void RopeHookItem::decrement(int value)
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

void RopeHookItem::resetCurrentState()
{
    compareAndSetState(1);
}

qreal RopeHookItem::min() const
{
    return minScale();
}
qreal RopeHookItem::max() const
{
    return maxScale();
}
void RopeHookItem::setMin(qreal v)
{
    setMinScale(v);
}
void RopeHookItem::setMax(qreal v)
{
    setMaxScale(v);
}

void RopeHookItem::parentScaleXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    emit scaleXChanged(_parentScaleXValue);
}

void RopeHookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    emit rotationChanged(_parentRotateValue);
}

void RopeHookItem::parentTranslateXChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateXValue=newValue;

    emit translateXChanged(_parentTranslateXValue);
}


void RopeHookItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        if(qFuzzyCompare(100 + _currentState, 100 + min()))
        {
            if(!_minIsReached)
            {
                emit minIsReached();
                _minIsReached = true;
            }
        }
        else
        {
            if(_minIsReached)
            {
                emit stopMinIsReached();
                _minIsReached=false;
            }
        }
        QTransform trans;
        trans.scale(1,_currentState);
        setTransform(trans);
        emit scaleYChanged(_currentState);
    }
}
