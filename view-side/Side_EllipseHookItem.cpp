#include "Side_EllipseHookItem.h"

using namespace Side;

EllipseHookItem::EllipseHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = EllipseHook;

    setId("ellipse_hook");
}

void EllipseHookItem::parentScaleXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void EllipseHookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void EllipseHookItem::parentTranslateXChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit translateXChanged(_parentTranslateXValue);
}
