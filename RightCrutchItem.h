#ifndef RIGHTCRUTCHITEM_H
#define RIGHTCRUTCHITEM_H

#include "AbstractItem.h"

class RightCrutchItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit RightCrutchItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void setCountSteps(int count);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v)
    {
        setMinY(v);
    }
    virtual void setMax(qreal v)
    {
        setMaxY(v);
    }

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

#endif // RIGHTCRUTCHITEM_H
