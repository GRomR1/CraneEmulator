#include "RopeHookItem.h"

RopeHookItem::RopeHookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type = RopeHook;
    _parentRotateValue=0;
    _parentScaleValue=1;
    _parentTranslateValue=0;
    _minIsReached=false;

    setId("rope_hook");
}

void RopeHookItem::increment()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();

    compareAndSetState(newState);
}

void RopeHookItem::decrement()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();

    compareAndSetState(newState);
}
void RopeHookItem::increment(int value)
{
    if(value < 0)
    {
        decrement(qAbs(value));
        return;
    }
    if(!value)
        return;
    qreal newState = _currentState;
    for(int i=0; i<value; i++)
    {
        newState += _currentStep;
        if(newState > max())
            newState = max();
    }
    compareAndSetState(newState);
}

void RopeHookItem::decrement(int value)
{
    if(value < 0)
    {
        increment(qAbs(value));
        return;
    }
    if(!value)
        return;
    qreal newState = _currentState;
    for(int i=0; i<value; i++)
    {
        newState -= _currentStep;
        if(newState < min())
            newState = min();
    }
    compareAndSetState(newState);
}

void RopeHookItem::resetCurrentState()
{
    compareAndSetState(1);
}

qreal RopeHookItem::min() const
{
    return minScale();
}
qreal RopeHookItem::max() const
{
    return maxScale();
}
void RopeHookItem::setMin(qreal v)
{
    setMinScale(v);
}
void RopeHookItem::setMax(qreal v)
{
    setMaxScale(v);
}

void RopeHookItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==EllipseHook)
    {
        _parentItem = dynamic_cast<EllipseHookItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
        connect(_parentItem, SIGNAL(rotationChanged(qreal)),
                this, SLOT(parentRotationChanged(qreal)));
        connect(_parentItem, SIGNAL(translateChanged(qreal)),
                this, SLOT(parentTranslateChanged(qreal)));
        setBasicPos(_parentItem->mapFromScene(pos()));
    }
}

void RopeHookItem::parentScaleChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentScaleValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    setTransform(trans);

    emit scaledChanged(_parentScaleValue);
}

void RopeHookItem::parentRotationChanged(qreal newValue)
{
    setPos(_parentItem->mapToScene(basicPos()));
    _parentRotateValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

    emit rotationChanged(_parentRotateValue);
}

void RopeHookItem::parentTranslateChanged(qreal newValue)
{
//    QPointF p = _parentItem->mapToScene(basicPos());
//    emit needDrawPoint(p);
    setPos(_parentItem->mapToScene(basicPos()));
    _parentTranslateValue=newValue;

//    QTransform trans;
//    trans.rotate(_parentRotateValue);
//    trans.translate(_parentTranslateValue,0);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

    emit translateChanged(_parentTranslateValue);
}


void RopeHookItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        _currentState = newState;
        if(qFuzzyCompare(100 + _currentState, 100 + min()))
        {
            if(!_minIsReached)
            {
                emit minIsReached();
                _minIsReached = true;
            }
        }
        else
        {
            if(_minIsReached)
            {
                emit stopMinIsReached();
                _minIsReached=false;
            }
        }
        QTransform trans;
        trans.scale(1,_currentState);
        setTransform(trans);
//        emit itemIsChanged(_type, Increment, _currentState);
        emit scaledYChanged(_currentState);
    }
}
