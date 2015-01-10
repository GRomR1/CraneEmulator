#ifndef TELESCOPICITEM_H
#define TELESCOPICITEM_H

#include "AbstractItem.h"
#include "OutriggerItem.h"

class TelescopicItem : public AbstractItem
{
    Q_OBJECT

public:
    explicit TelescopicItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v);
    virtual void setMax(qreal v);

    virtual void setParentItemMy(AbstractItem *item);

signals:
    void scaledChanged(qreal newScale);
    void rotationChanged(qreal newScale);
    void translateChanged(qreal newValue);

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

protected:
    OutriggerItem *_parentItem;
    qreal _parentScaleValue;
    qreal _parentRotateValue;

    virtual void compareAndSetState(qreal newState);

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);

};

#endif // TELESCOPICITEM_H
