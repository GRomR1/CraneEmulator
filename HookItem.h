#ifndef HOOKITEM_H
#define HOOKITEM_H

#include "AbstractItem.h"

class HookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit HookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void setCountSteps(int count);

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

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

public slots:
    virtual void increment();
    virtual void decrement();

};

#endif // HOOKITEM_H
