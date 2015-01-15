#ifndef TELESCOPICITEMTOP_H
#define TELESCOPICITEMTOP_H

#include "../AbstractItem.h"
namespace Top {

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

#endif // TELESCOPICITEMTOP_H
