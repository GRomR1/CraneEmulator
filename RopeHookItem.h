#ifndef ROPEHOOKITEM_H
#define ROPEHOOKITEM_H

#include "AbstractItem.h"
#include "EllipseHookItem.h"

class RopeHookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void setCountSteps(int count);
    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v)
    {
        Q_UNUSED(v);
        //TODO продумать минимальное состояние троса
    }
    virtual void setMax(qreal v)
    {
        Q_UNUSED(v);
        //TODO продумать максимальное состояние троса
    }
    virtual void setParentItemMy(AbstractItem *item);

public slots:
    virtual void increment();
    virtual void decrement();

signals:
    void scaledChanged(qreal value);
    void rotationChanged(qreal value);
    void translateChanged(qreal value);

protected:
    qreal _parentScaleValue;
    qreal _parentRotateValue;
    qreal _parentTranslateValue;
    EllipseHookItem *_parentItem;

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);
    void parentTranslateChanged(qreal newValue);

};

#endif // ROPEHOOKITEM_H
