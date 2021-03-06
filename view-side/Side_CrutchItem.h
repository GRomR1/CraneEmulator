#ifndef CRUTCHITEMSIDE_H
#define CRUTCHITEMSIDE_H

#include "../AbstractItem.h"
namespace Side {

class CrutchItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit CrutchItem(int type, QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v);
    virtual void setMax(qreal v);

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

protected:
    virtual void compareAndSetState(qreal newState);

};

}


#endif // CRUTCHITEMSIDE_H
