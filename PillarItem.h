#ifndef PILLARITEM_H
#define PILLARITEM_H

#include "AbstractItem.h"

class PillarItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit PillarItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    virtual void resetCurrentState();

    virtual qreal min() const;
    virtual qreal max() const;
    virtual void setMin(qreal v)
    {
        setMinAngle(v);
    }
    virtual void setMax(qreal v)
    {
        setMaxAngle(v);
    }


signals:
    void scaledChanged(qreal newScale);

public slots:
    virtual void increment(); //поворот стойки по часовой стрелке на 1 шаг
    virtual void decrement(); //поворот стойки против часовой стрелке на 1 шаг
    virtual void increment(int value);//поворот стойки по часовой стрелке на value шагов
    virtual void decrement(int value);//поворот стойки против часовой стрелке на value шагов

protected:
    virtual void compareAndSetState(qreal newState);
};

#endif // PILLARITEM_H
