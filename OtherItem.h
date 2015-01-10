#ifndef OTHERITEM_H
#define OTHERITEM_H

#include "AbstractItem.h"

class OtherItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual qreal min() const
    {
        return 0;
    }
    virtual qreal max() const
    {
        return 0;
    }
    virtual void setMin(qreal v)
    {
        Q_UNUSED(v);
    }
    virtual void setMax(qreal v)
    {
        Q_UNUSED(v);
    }

public slots:
    virtual void increment()
    {
    }
    virtual void decrement()
    {
    }

};

#endif // OTHERITEM_H
