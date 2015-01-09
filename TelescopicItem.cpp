#include "TelescopicItem.h"

TelescopicItem::TelescopicItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = Telescopic;
    setId("telescopic");

    _parentScaleValue=1;
    _parentRotateValue=0;
}

//QVariant TelescopicItem::itemChange(GraphicsItemChange change, const QVariant & value)
//{
//    emit signalItemChanged(change);
//    return AbstractItem::itemChange(change, value);
//}

void TelescopicItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
//    _currentState = newState;

//    resetTransform();
//    QTransform trans = transform();
//    trans.translate(_currentState,0);
//    setTransform(trans);

//    emit itemIsChanged(_type, Increment, _currentState);
    compareAndSetState(newState);
}

void TelescopicItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
//    _currentState = newState;

//    resetTransform();
//    QTransform trans = transform();
//    trans.translate(_currentState,0);
//    setTransform(trans);

//    emit itemIsChanged(_type, Decrement, _currentState);
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
void TelescopicItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

void TelescopicItem::resetCurrentState()
{
//    AbstractItem::resetCurrentState();
//    resetTransform();

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

void TelescopicItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==Outrigger)
    {
        _parentItem = dynamic_cast<OutriggerItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void TelescopicItem::parentScaleChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
//    qDebug() << "current pos: " << pos();
//    qDebug() << "item coord in parent coord: " << basicPos();
//    qDebug() << "to parrent pos: " << mapToItem(_parentItem, basicPos());
//    qDebug() << "parent from scene" << _parentItem->mapToScene(basicPos());

    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleValue,1);
    trans.translate(_currentState,0);
    setTransform(trans);

    emit scaledChanged(_parentScaleValue);
}

void TelescopicItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleValue,1);
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
        trans.scale(_parentScaleValue,1);
        trans.translate(_currentState,0);
        setTransform(trans);
//        emit itemIsChanged(_type, Increment, _currentState);
        emit translateChanged(_currentState);
    }
}
