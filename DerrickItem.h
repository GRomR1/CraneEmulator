#ifndef DERRICKITEM_H
#define DERRICKITEM_H

#include "AbstractItem.h"
//#include "OutriggerItem.h"
#include "PillarItem.h"

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

    virtual void setParentItemMy(AbstractItem *item);

signals:
    void scaledChanged(qreal newScale);
    void rotationChanged(qreal newScale);

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

private slots:
    void parentScaleChanged(qreal newValue);

protected:
    qreal _lastScaleValue;
    PillarItem *_parentItem;

    virtual void compareAndSetState(qreal newState);

};

#endif // DERRICKITEM_H
