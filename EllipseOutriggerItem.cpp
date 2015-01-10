#include "EllipseOutriggerItem.h"

EllipseOutriggerItem::EllipseOutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = EllipseOutrigger;
    _lastRotateValue=0;
    _lastScaleValue=1;
    setId("ellipse_outrigger");
}

void EllipseOutriggerItem::increment()
{
}

void EllipseOutriggerItem::decrement()
{
}

qreal EllipseOutriggerItem::min() const
{
    return 0;
}

qreal EllipseOutriggerItem::max() const
{
    return 0;
}

void EllipseOutriggerItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==Derrick)
    {
        _parentItem = dynamic_cast<DerrickItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void EllipseOutriggerItem::parentScaleChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
//    qDebug() << "current pos: " << pos();
//    qDebug() << "item coord in parent coord: " << basicPos();
//    qDebug() << "to parrent pos: " << mapToItem(_parentItem, basicPos());
//    qDebug() << "parent from scene" << _parentItem->mapToScene(basicPos());

    setPos(_parentItem->mapToScene(basicPos()));
    _lastScaleValue=newValue;

//    QTransform trans;
//    trans.rotate(_lastRotateValue);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

    emit scaledChanged(_lastScaleValue);
}

void EllipseOutriggerItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _lastRotateValue=newValue;

    QTransform trans;
    trans.rotate(_lastRotateValue);
//    trans.scale(_lastScaleValue,1);
    setTransform(trans);

    emit rotationChanged(_lastRotateValue);
}
