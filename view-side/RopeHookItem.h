#ifndef ROPEHOOKITEM_H
#define ROPEHOOKITEM_H

#include "../AbstractItem.h"
namespace Side {

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

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

signals:
    void minIsReached();
    void stopMinIsReached();

protected:
    bool _minIsReached;
    virtual void compareAndSetState(qreal newState);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);
    virtual void parentTranslateXChanged(qreal newValue);

};

}

#endif // ROPEHOOKITEM_H
