#include "RopeHookItem.h"

RopeHookItem::RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = RopeHook;
}

QVariant RopeHookItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    emit signalItemChanged(change);
//    qDebug() << "rope was changed" << change;
    if(change == QGraphicsItem::ItemRotationChange && scene())
    {
        qDebug() << "rope was rotated";
        return QVariant();
    }
    return AbstractItem::itemChange(change, value);
}


void RopeHookItem::slotItemChanged(GraphicsItemChange change)
{
    if(change == QGraphicsItem::ItemRotationChange && scene())
    {
        qDebug() << "rope was rotated";
        qDebug() << rotation();
    }
}


void RopeHookItem::slotRotationChanged()
{
    AbstractItem *item = dynamic_cast<AbstractItem *>(sender());
    qDebug() << item->rotation();
}

void RopeHookItem::increment()
{
    //TODO продумать увеличение троса
//    qreal newState = _currentState + _currentStep;
//    if(newState > maxAngle())
//        newState = maxAngle();
//    _currentState = newState;
    emit itemIsChanged(_type, Increment, _currentState);
}

void RopeHookItem::decrement()
{
    //TODO продумать уменьшение троса
//    qreal newState = _currentState - _currentStep;
//    if(newState > minAngle())
//        newState = maxAngle();
//    _currentState = newState;
    emit itemIsChanged(_type, Decrement, _currentState);
}

void RopeHookItem::setCountSteps(int count)
{
    //TODO продумать просчет количесвта шагов троса
//    if(count <= 0)
//        return;
    _countSteps = count;
//    _currentStep=( qAbs(minAngle()) + qAbs(maxAngle()) ) / _countSteps;
}

qreal RopeHookItem::min() const
{
    //TODO продумать минимальное состояние троса
    return 0;
}

qreal RopeHookItem::max() const
{
    //TODO продумать максимальное состояние троса
    return 0;
}
