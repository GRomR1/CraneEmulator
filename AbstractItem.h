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
    EllipseDerick, RectPillar,
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
    virtual qreal min() const {return qreal();}
    virtual qreal max() const {return qreal();}
    virtual void setMin(qreal v) {Q_UNUSED(v)}
    virtual void setMax(qreal v) {Q_UNUSED(v)}

    void setValue(qreal v);
    qreal value() const;
    int countSteps() const;
    qreal currentStep() const;
    qreal currentState() const;
    virtual void setCountSteps(int count);

    QPointF basicPos();
    void setBasicPos(QPointF p);

    virtual void setParentItemMy(AbstractItem *item);

signals:
    void scaleXChanged(qreal value);
    void scaleYChanged(qreal value);
    void rotationChanged(qreal value);
    void translateXChanged(qreal value);
    void translateYChanged(qreal value);

    void needDrawPoint(QPointF p); //для отладки - соединить со слотом отрисовки точки

public slots:
    virtual void increment(){}
    virtual void decrement(){}
    virtual void increment(int value){Q_UNUSED(value)}
    virtual void decrement(int value){Q_UNUSED(value)}

protected slots:
    virtual void parentScaleXChanged(qreal newValue){Q_UNUSED(newValue)}
    virtual void parentScaleYChanged(qreal newValue){Q_UNUSED(newValue)}
    virtual void parentRotationChanged(qreal newValue){Q_UNUSED(newValue)}
    virtual void parentTranslateXChanged(qreal newValue){Q_UNUSED(newValue)}
    virtual void parentTranslateYChanged(qreal newValue){Q_UNUSED(newValue)}

protected:
    AbstractItem *_parentItem;
    qreal _parentScaleXValue;
    qreal _parentScaleYValue;
    qreal _parentRotateValue;
    qreal _parentTranslateXValue;
    qreal _parentTranslateYValue;

    QSvgRenderer *_renderer;
    int _type;
    qreal _minAngle;
    qreal _maxAngle;
    QPointF _basicPos;

    QPointF _pointMin;
    QPointF _pointMax;

    qreal _minScale;
    qreal _maxScale;

    int _countSteps;
    qreal _currentStep;
    qreal _currentState; //угол отклонения, абсцисса/ордината точки выдвижения, и пр.

    //для деталей(derrick, outrigger) которые можно повернуть(наклонить) вверх/вниз
    qreal minAngle() const;
    qreal maxAngle() const;
    void setMinAngle(qreal angle);
    void setMaxAngle(qreal angle);

    //для деталей(telesopic, crutches) которые перемещаются вдоль одной из осей
    qreal minX() const;
    qreal minY() const;
    qreal maxX() const;
    qreal maxY() const;
    void setMaxX(qreal v);
    void setMaxY(qreal v);
    void setMinX(qreal v);
    void setMinY(qreal v);

    //для деталей(rope hook), которые изменают свой масштаб/длину
    qreal minScale() const;
    qreal maxScale() const;
    void setMinScale(qreal v);
    void setMaxScale(qreal v);


};

#endif // ABSTRACTITEM_H
