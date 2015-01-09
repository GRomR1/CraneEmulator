#include "EllipseHookItem.h"

EllipseHookItem::EllipseHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = EllipseHook;
    _parentRotateValue=0;
    _parentScaleValue=1;
    _parentTranslateValue=0;

    setId("ellipse_hook");
}

void EllipseHookItem::increment()
{
}

void EllipseHookItem::decrement()
{
}

qreal EllipseHookItem::min() const
{
    return 0;
}

qreal EllipseHookItem::max() const
{
    return 0;
}

void EllipseHookItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==Telescopic)
    {
        _parentItem = dynamic_cast<TelescopicItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        connect(_parentItem, SIGNAL(translateChanged(qreal)),
                this, SLOT(parentTranslateChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void EllipseHookItem::parentScaleChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
//    trans.scale(_lastScaleValue,1);
    setTransform(trans);

    emit scaledChanged(_parentScaleValue);
}

void EllipseHookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
//    trans.scale(_lastScaleValue,1);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void EllipseHookItem::parentTranslateChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
//    trans.translate(_parentTranslateValue,0);
//    trans.scale(_lastScaleValue,1);
    setTransform(trans);

    emit translateChanged(_parentTranslateValue);
}
