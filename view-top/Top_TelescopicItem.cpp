#include "Top_TelescopicItem.h"

using namespace Top;

TelescopicItem::TelescopicItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Telescopic;
    setId("telescopic");
}


void TelescopicItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void TelescopicItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}
void TelescopicItem::increment(int value)
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


void TelescopicItem::decrement(int value)
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

void TelescopicItem::resetCurrentState()
{
    compareAndSetState(0);
}

qreal TelescopicItem::min() const
{
    return minX();
}

qreal TelescopicItem::max() const
{
   return maxX();
}

void TelescopicItem::setMin(qreal v)
{
    setMinX(v);
}
void TelescopicItem::setMax(qreal v)
{
    setMaxX(v);
}


void TelescopicItem::parentScaleXChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
//    qDebug() << "current pos: " << pos();
//    qDebug() << "item coord in parent coord: " << basicPos();
//    qDebug() << "to parrent pos: " << mapToItem(_parentItem, basicPos());
//    qDebug() << "parent from scene" << _parentItem->mapToScene(basicPos());

    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    trans.translate(_currentState,0);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void TelescopicItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    trans.translate(_currentState,0);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void TelescopicItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        QTransform trans;
        trans.rotate(_parentRotateValue);
        trans.scale(_parentScaleXValue,1);
        trans.translate(_currentState,0);
        setTransform(trans);
        emit translateXChanged(_currentState);
    }
}
