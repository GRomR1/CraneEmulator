#include "TelescopicItem.h"

TelescopicItem::TelescopicItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Telescopic;
    setId("telescopic");
}

QVariant TelescopicItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
//    qDebug() << "telescopic was changed" << change;
    emit signalItemChanged(change);
    return AbstractItem::itemChange(change, value);
}

void TelescopicItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(_currentState,0);
    setTransform(trans);

    emit itemIsChanged(_type, Increment, _currentState);
}

void TelescopicItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
    _currentState = newState;

    resetTransform();
    QTransform trans = transform();
    trans.translate(_currentState,0);
    setTransform(trans);

    emit itemIsChanged(_type, Decrement, _currentState);
}

void TelescopicItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

void TelescopicItem::resetCurrentState()
{
    AbstractItem::resetCurrentState();
    resetTransform();
}

qreal TelescopicItem::min() const
{
    return minX();
}

qreal TelescopicItem::max() const
{
   return maxX();
}
