#ifndef DERRICKITEMTOP_H
#define DERRICKITEMTOP_H

#include "../AbstractItem.h"
namespace Top {

class DerrickItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit DerrickItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
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

protected slots:
    virtual void parentRotationChanged(qreal newValue);

protected:
    virtual void compareAndSetState(qreal newState);

};

}

#endif // DERRICKITEMTOP_H
