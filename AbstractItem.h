#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QDebug>
#include <math.h>

static const int DefaultCountSteps = 10;
static const qreal DefaultMinAngle = 0;
static const qreal DefaultMaxAngle = 180;

namespace AbstractItems {
enum TypeItem
{
    LeftCrutch = QGraphicsItem::UserType + 1,
    RightCrutch,
    Pillar,
    EllipseDerick,
    Derrick,
    EllipseOutrigger,
    Outrigger,
    Telescopic,
    EllipseHook,
    RopeHook,
    Hook,
    Ground,
    Abstract
};

enum Action
{
    Increment = 1,
    Decrement,
    Reset
};
}

using namespace AbstractItems;

class AbstractItem : public QGraphicsSvgItem
{
    Q_OBJECT

public:
    explicit AbstractItem(QSvgRenderer *renderer, QGraphicsItem *parent = 0);
    void setId(QString id);
    virtual int type() const;
    virtual void resetCurrentState();

    virtual qreal min() const = 0;
    virtual qreal max() const = 0;
    virtual void setMin(qreal v) = 0;
    virtual void setMax(qreal v) = 0;

    int countSteps() const;
    qreal currentStep() const;
    virtual void setCountSteps(int count)=0;
//    virtual void addChild(AbstractItem *);

    QPointF basicPos();
    void setBasicPos(QPointF p);

public slots:
    //служит для обработки изменения состояния у объектов-предков
    //отправляет сигнал signalItemChanged
    virtual void slotItemChanged(GraphicsItemChange change);

    virtual void increment()=0;
    virtual void decrement()=0;

    virtual void increment(int value);
    virtual void decrement(int value);

signals:
    void signalItemChanged(GraphicsItemChange change);
    void itemIsChanged(int itemType, Action action, qreal value);

    void needDrawPoint(QPointF p);

protected:
    QSvgRenderer *_renderer;
    int _type;
    qreal _minAngle;
    qreal _maxAngle;
    QPointF _basicPos;

    QPointF _pointMin;
    QPointF _pointMax;

    int _countSteps;
    qreal _currentStep;
    qreal _currentState; //угол отклонения, абсцисса/ордината точки выдвижения, и пр.

//    virtual void compareAndSetState(qreal newState);

    //для деталей которые можно повернуть(наклонить) вверх/вниз
    qreal minAngle() const;
    qreal maxAngle() const;
    void setMinAngle(qreal angle);
    void setMaxAngle(qreal angle);

    //для деталей которые перемещаются вдоль одной из осей
    qreal minX() const;
    qreal minY() const;
    qreal maxX() const;
    qreal maxY() const;
    void setMaxX(qreal v);
    void setMaxY(qreal v);
    void setMinX(qreal v);
    void setMinY(qreal v);
};

#endif // ABSTRACTITEM_H
