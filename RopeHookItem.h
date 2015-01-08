#ifndef ROPEHOOKITEM_H
#define ROPEHOOKITEM_H

#include "AbstractItem.h"

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

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

public slots:
    //служит для обработки изменения состояния у объектов-предков
    //отправляет сигнал signalItemChanged
    void slotItemChanged(GraphicsItemChange change);
    void slotRotationChanged();

public slots:
    virtual void increment();
    virtual void decrement();


};

#endif // ROPEHOOKITEM_H
