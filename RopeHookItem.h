#ifndef ROPEHOOKITEM_H
#define ROPEHOOKITEM_H

#include "AbstractItem.h"
#include "EllipseHookItem.h"

class RopeHookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v);
    virtual void setMax(qreal v);
    virtual void setParentItemMy(AbstractItem *item);

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

signals:
    void scaledChanged(qreal value);
    void scaledYChanged(qreal value);
    void rotationChanged(qreal value);
    void translateChanged(qreal value);
    void minIsReached();
    void stopMinIsReached();

protected:
    qreal _parentScaleValue;
    qreal _parentRotateValue;
    qreal _parentTranslateValue;
    EllipseHookItem *_parentItem;
    bool _minIsReached;
    virtual void compareAndSetState(qreal newState);

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);
    void parentTranslateChanged(qreal newValue);

};

#endif // ROPEHOOKITEM_H
