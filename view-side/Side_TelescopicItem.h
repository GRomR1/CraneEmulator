#ifndef TELESCOPICITEMSIDE_H
#define TELESCOPICITEMSIDE_H

#include "../AbstractItem.h"
namespace Side {

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

public slots:
    virtual void increment();
    virtual void decrement();
    virtual void increment(int value);
    virtual void decrement(int value);

protected:
    virtual void compareAndSetState(qreal newState);

protected slots:
    virtual void parentScaleXChanged(qreal newValue);
    virtual void parentRotationChanged(qreal newValue);

};

}

#endif // TELESCOPICITEMSIDE_H
