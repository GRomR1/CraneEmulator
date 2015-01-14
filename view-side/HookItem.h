#ifndef HOOKITEM_H
#define HOOKITEM_H

#include "../AbstractItem.h"
namespace Side {

class HookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit HookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);
    virtual void parentTranslateXChanged(qreal newValue);
    virtual void parentScaleYChanged(qreal newValue);

};

}

#endif // HOOKITEM_H
