#include "Side_OutriggerItem.h"

using namespace Side;

OutriggerItem::OutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Outrigger;
    setId("outrigger");
}


void OutriggerItem::resetCurrentState()
{
    compareAndSetState(0);
}

void OutriggerItem::increment()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}

void OutriggerItem::decrement()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void OutriggerItem::increment(int value)
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

void OutriggerItem::decrement(int value)
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

qreal OutriggerItem::min() const
{
    return minAngle();
}

qreal OutriggerItem::max() const
{
    return maxAngle();
}

void OutriggerItem::setMin(qreal v)
{
    setMinAngle(v);
}
void OutriggerItem::setMax(qreal v)
{
    setMaxAngle(v);
}

void OutriggerItem::parentScaleXChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
//    qDebug() << "current pos: " << pos();
//    qDebug() << "item coord in parent coord: " << basicPos();
//    qDebug() << "to parrent pos: " << mapToItem(_parentItem, basicPos());
//    qDebug() << "parent from scene" << _parentItem->mapToScene(basicPos());

    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_currentState+_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void OutriggerItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_currentState+_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit rotationChanged(_currentState+_parentRotateValue);
}

void OutriggerItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        QTransform trans;
        trans.rotate(_currentState+_parentRotateValue);
        trans.scale(_parentScaleXValue,1);
        setTransform(trans);
//        emit itemIsChanged(_type, Increment, _currentState);
        emit rotationChanged(_currentState+_parentRotateValue);
    }
}
