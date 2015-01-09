#ifndef ELLIPSEOUTRIGGERITEM_H
#define ELLIPSEOUTRIGGERITEM_H

#include "AbstractItem.h"
#include "DerrickItem.h"

class EllipseOutriggerItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit EllipseOutriggerItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void setCountSteps(int count)
    {
        Q_UNUSED(count);
    }
    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v)
    {
        Q_UNUSED(v);
    }
    virtual void setMax(qreal v)
    {
        Q_UNUSED(v);
    }
    virtual void setParentItemMy(AbstractItem *item);

signals:
    void scaledChanged(qreal newScale);
    void rotationChanged(qreal newScale);

public slots:
    virtual void increment();
    virtual void decrement();

protected:
    qreal _lastScaleValue;
    qreal _lastRotateValue;
    DerrickItem *_parentItem;

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);

};

#endif // ELLIPSEOUTRIGGERITEM_H
