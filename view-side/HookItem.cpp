#include "HookItem.h"

using namespace Side;

HookItem::HookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Hook;
    _parentRotateValue=0;
    setId("hook");
}

void HookItem::parentScaleXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    emit scaleXChanged(_parentScaleXValue);
}
void HookItem::parentScaleYChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleYValue=newValue;

    emit scaleYChanged(_parentScaleYValue);
}
void HookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    emit rotationChanged(_parentRotateValue);
}

void HookItem::parentTranslateXChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateXValue=newValue;

    emit translateXChanged(_parentTranslateXValue);
}


