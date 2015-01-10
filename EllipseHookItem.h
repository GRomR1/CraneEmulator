#ifndef ELLIPSEHOOKITEM_H
#define ELLIPSEHOOKITEM_H

#include "AbstractItem.h"
#include "TelescopicItem.h"

class EllipseHookItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit EllipseHookItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);

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
    void rotationChanged(qreal value);
    void translateChanged(qreal value);

public slots:
    virtual void increment();
    virtual void decrement();

protected:
    qreal _parentScaleValue;
    qreal _parentRotateValue;
    qreal _parentTranslateValue;
    TelescopicItem *_parentItem;

private slots:
    void parentScaleChanged(qreal newValue);
    void parentRotationChanged(qreal newValue);
    void parentTranslateChanged(qreal newValue);

};

#endif // ELLIPSEHOOKITEM_H
