#ifndef DERRICKITEM_H
#define DERRICKITEM_H

#include "AbstractItem.h"

class DerrickItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit DerrickItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void setCountSteps(int count);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v)
    {
        setMinAngle(v);
    }
    virtual void setMax(qreal v)
    {
        setMaxAngle(v);
    }

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

public slots:
    virtual void increment();
    virtual void decrement();

    virtual void increment(int value)
    {
        AbstractItem::increment(value);
    }
    virtual void decrement(int value)
    {
        AbstractItem::decrement(value);
    }

};

#endif // DERRICKITEM_H
