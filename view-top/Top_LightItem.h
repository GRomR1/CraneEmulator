#ifndef TOP_LIGHTITEM_H
#define TOP_LIGHTITEM_H

#include "../AbstractItem.h"
namespace Top {

class LightItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit LightItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);
    virtual void parentTranslateXChanged(qreal newValue);

};

}

#endif // TOP_LIGHTITEM_H
