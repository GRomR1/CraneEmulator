#include "RopeHookItem.h"

RopeHookItem::RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = RopeHook;
    _parentRotateValue=0;
    _parentScaleValue=1;
    _parentTranslateValue=0;

    setId("rope_hook");
}

//QVariant RopeHookItem::itemChange(GraphicsItemChange change, const QVariant & value)
//{
//    emit signalItemChanged(change);
////    qDebug() << "rope was changed" << change;
//    if(change == QGraphicsItem::ItemRotationChange && scene())
//    {
//        qDebug() << "rope was rotated";
//        return QVariant();
//    }
//    return AbstractItem::itemChange(change, value);
//}


//void RopeHookItem::slotItemChanged(GraphicsItemChange change)
//{
//    if(change == QGraphicsItem::ItemRotationChange && scene())
//    {
//        qDebug() << "rope was rotated";
//        qDebug() << rotation();
//    }
//}


//void RopeHookItem::slotRotationChanged()
//{
//    AbstractItem *item = dynamic_cast<AbstractItem *>(sender());
//    qDebug() << item->rotation();
//}

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

void RopeHookItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==EllipseHook)
    {
        _parentItem = dynamic_cast<EllipseHookItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        connect(_parentItem, SIGNAL(translateChanged(qreal)),
                this, SLOT(parentTranslateChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void RopeHookItem::parentScaleChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    setTransform(trans);

    emit scaledChanged(_parentScaleValue);
}

void RopeHookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void RopeHookItem::parentTranslateChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    trans.translate(_parentTranslateValue,0);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

    emit translateChanged(_parentTranslateValue);
}
