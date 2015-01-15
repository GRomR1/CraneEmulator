#include "Top_OutriggerItem.h"

using namespace Top;

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

    qreal cosValue = cos((double)_currentState*M_PI/180.);
    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue*cosValue,1);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void OutriggerItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    qreal cosValue = cos((double)_currentState*M_PI/180.);
    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue*cosValue,1);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void OutriggerItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        qreal cosValue = cos((double)_currentState*M_PI/180.);
        QTransform trans;
        trans.rotate(_parentRotateValue);
        trans.scale(_parentScaleXValue*cosValue,1);
        setTransform(trans);
        emit scaleXChanged(_parentScaleXValue*cosValue);
    }
}
