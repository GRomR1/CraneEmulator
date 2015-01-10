#ifndef HOOKITEM_H
#define HOOKITEM_H

#include "AbstractItem.h"
#include "RopeHookItem.h"

class HookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit HookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

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

    virtual void setParentItemMy(AbstractItem *item);

signals:
    void scaledChanged(qreal value);
    void scaledYChanged(qreal value);
    void rotationChanged(qreal value);
    void translateChanged(qreal value);

public slots:
    virtual void increment();
    virtual void decrement();

protected:
    qreal _parentScaleValue;
    qreal _parentScaleYValue;
    qreal _parentRotateValue;
    qreal _parentTranslateValue;
    RopeHookItem *_parentItem;

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);
    void parentTranslateChanged(qreal newValue);
    void parentScaledYChanged(qreal newValue);

};

#endif // HOOKITEM_H
