#include "HookItem.h"

HookItem::HookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Hook;
    _parentRotateValue=0;
    _parentScaleValue=1;
    _parentScaleYValue=1;
    _parentTranslateValue=0;

    setId("hook");
}


void HookItem::increment()
{
}

void HookItem::decrement()
{
}

qreal HookItem::min() const
{
    return 0;
}

qreal HookItem::max() const
{
    return 0;
}
void HookItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==RopeHook)
    {
        _parentItem = dynamic_cast<RopeHookItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        connect(_parentItem, SIGNAL(translateChanged(qreal)),
                this, SLOT(parentTranslateChanged(qreal)));
        connect(_parentItem, SIGNAL(scaledYChanged(qreal)),
                this, SLOT(parentScaledYChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void HookItem::parentScaleChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleValue=newValue;

    emit scaledChanged(_parentScaleValue);
}
void HookItem::parentScaledYChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleYValue=newValue;

    emit scaledYChanged(_parentScaleYValue);
}
void HookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    emit rotationChanged(_parentRotateValue);
}

void HookItem::parentTranslateChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateValue=newValue;

    emit translateChanged(_parentTranslateValue);
}


