#include "Top_LightItem.h"

using namespace Top;

LightItem::LightItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    setId("light_on");
}

void LightItem::parentScaleXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void LightItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void LightItem::parentTranslateXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit translateXChanged(_parentTranslateXValue);
}
