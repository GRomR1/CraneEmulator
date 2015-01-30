#include "Side_LightItem.h"

using namespace Side;

LightItem::LightItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=typeItem;
    if(_type==LightOn)
        setId("lightOn");
    if(_type==LampLight)
        setId("lamp");
}

void LightItem::parentScaleXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit scaleXChanged(_parentScaleXValue);
}

void LightItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void LightItem::parentTranslateXChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateXValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    trans.scale(_parentScaleXValue,1);
    setTransform(trans);

    emit translateXChanged(_parentTranslateXValue);
}
