#ifndef LEFTCRUTCHITEM_H
#define LEFTCRUTCHITEM_H

#include "AbstractItem.h"

class LeftCrutchItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit LeftCrutchItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
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

#endif // LEFTCRUTCHITEM_H
