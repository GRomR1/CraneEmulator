#ifndef ELLIPSEHOOKITEMSIDE_H
#define ELLIPSEHOOKITEMSIDE_H

#include "../AbstractItem.h"
namespace Side {

class EllipseHookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit EllipseHookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);
    virtual void parentTranslateXChanged(qreal newValue);

};

}

#endif // ELLIPSEHOOKITEMSIDE_H
