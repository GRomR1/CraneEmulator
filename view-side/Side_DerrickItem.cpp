#include "Side_DerrickItem.h"

using namespace Side;

DerrickItem::DerrickItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Derrick;
    setId("derrick");

    QPointF p(0, boundingRect().height()/2);
    setTransformOriginPoint(p);
}

void DerrickItem::increment()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}


void DerrickItem::decrement()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void DerrickItem::increment(int value)
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


void DerrickItem::decrement(int value)
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

void DerrickItem::resetCurrentState()
{
    compareAndSetState(0);
}

qreal DerrickItem::min() const
{
    return minAngle();
}

qreal DerrickItem::max() const
{
    return maxAngle();
}

void DerrickItem::setMin(qreal v)
{
    setMinAngle(v);
}
void DerrickItem::setMax(qreal v)
{
    setMaxAngle(v);
}

void DerrickItem::parentScaleXChanged(qreal newValue)
{
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_currentState);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}


void DerrickItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        QTransform trans;
        trans.rotate(_currentState);
        trans.scale(_parentScaleXValue,1);
        setTransform(trans);
        emit rotationChanged(_currentState);
    }
}
