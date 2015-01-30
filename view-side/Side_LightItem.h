#ifndef SIDE_LIGHTITEM_H
#define SIDE_LIGHTITEM_H

#include "../AbstractItem.h"
namespace Side {

class LightItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit LightItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent = 0);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);
    virtual void parentTranslateXChanged(qreal newValue);

};

}

#endif // SIDE_LIGHTITEM_H
