#ifndef ELLIPSEOUTRIGGERITEMSIDE_H
#define ELLIPSEOUTRIGGERITEMSIDE_H

#include "../AbstractItem.h"
namespace Side {

class EllipseOutriggerItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit EllipseOutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);

};

}

#endif // ELLIPSEOUTRIGGERITEMSIDE_H
