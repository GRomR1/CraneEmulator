#include "EllipseOutriggerItem.h"

using namespace Side;

EllipseOutriggerItem::EllipseOutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = EllipseOutrigger;
    setId("ellipse_outrigger");
}

void EllipseOutriggerItem::parentScaleXChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
//    qDebug() << "current pos: " << pos();
//    qDebug() << "item coord in parent coord: " << basicPos();
//    qDebug() << "to parrent pos: " << mapToItem(_parentItem, basicPos());
//    qDebug() << "parent from scene" << _parentItem->mapToScene(basicPos());

    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleXValue=newValue;

    emit scaleXChanged(_parentScaleXValue);
}

void EllipseOutriggerItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

    QTransform trans;
    trans.rotate(_parentRotateValue);
    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}
