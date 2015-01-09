#include "DerrickItem.h"

DerrickItem::DerrickItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Derrick;
    _lastScaleValue = 1.;
    setId("derrick");

    QPointF p(0, boundingRect().height()/2);
    setTransformOriginPoint(p);
}

//QVariant DerrickItem::itemChange(GraphicsItemChange change, const QVariant & value)
//{
//    emit signalItemChanged(change);
//    return AbstractItem::itemChange(change, value);
//}

void DerrickItem::increment()
{
    qreal newState = _currentState - _currentStep;
    if(newState < min())
        newState = min();
//    _currentState = newState;

    compareAndSetState(newState);

//    resetTransform();
//    QTransform trans = transform();
//    trans.rotate(_currentState);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

//    childChangePos();
//    childRotate();

//    emit itemIsChanged(_type, Increment, _currentState);
}

//void DerrickItem::addChild(AbstractItem *item)
//{
//    if(item && item->type()==Outrigger)
//        _childOutrigger = dynamic_cast<OutriggerItem *>(item);
//}

//void DerrickItem::childChangePos()
//{
//    QPointF p(mapToScene(_basicOutriggerPos));
////    qDebug() << p;
//    _childOutrigger->setPos(p);
//}

//void DerrickItem::childRotate()
//{
//    _childOutrigger->setRotation(_currentState);
//}

//void DerrickItem::childScale()
//{
//    QTransform trans = _childOutrigger->transform();
//    trans.scale(_lastScaleValue,1);
//    _childOutrigger->setTransform(trans);
//}

//void DerrickItem::childResetTransformation()
//{
//    _childOutrigger->resetTransform();
//    childChangePos();
//    childRotate();
//    childScale();
//}

//void DerrickItem::setChildBasicPos(int typeItem, QPointF p)
//{
//    if((TypeItem)typeItem == Outrigger)
//        _basicOutriggerPos = p;
//}

void DerrickItem::decrement()
{
    qreal newState = _currentState + _currentStep;
    if(newState > max())
        newState = max();
//    _currentState = newState;

//    resetTransform();
//    QTransform trans = transform();
//    trans.rotate(_currentState);
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);

//    childChangePos();
//    childRotate();

//    emit itemIsChanged(_type, Decrement, _currentState);

    compareAndSetState(newState);
}

void DerrickItem::increment(int value)
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
        newState -= _currentStep;
        if(newState < min())
            newState = min();
    }
    compareAndSetState(newState);
}


void DerrickItem::decrement(int value)
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
        newState += _currentStep;
        if(newState > max())
            newState = max();
    }
    compareAndSetState(newState);
}

void DerrickItem::setParentItemMy(AbstractItem *item)
{
    if(item && item->type()==Pillar)
    {
        _parentItem = dynamic_cast<PillarItem *>(item);
        connect(_parentItem, SIGNAL(scaledChanged(qreal)),
                this, SLOT(parentScaleChanged(qreal)));
    }
}

void DerrickItem::setCountSteps(int count)
{
    if(count <= 0)
        return;
    _countSteps = count;
    _currentStep=( qAbs(min()) + qAbs(max()) ) / _countSteps;
}

void DerrickItem::resetCurrentState()
{
//    AbstractItem::resetCurrentState();
//    resetTransform();
//    QTransform trans;
//    trans.scale(_lastScaleValue,1);
//    setTransform(trans);
//    childChangePos();
//    childRotate();
//    childScale();
    compareAndSetState(0);
}


qreal DerrickItem::min() const
{
    return minAngle();
}

qreal DerrickItem::max() const
{
    return maxAngle();
}

//void DerrickItem::actionAfterPillarRotate(int itemType, Action action, qreal value)
//{
//    if((TypeItem)itemType == Pillar)
//    {
//        QTransform trans = transform();
//        if(action==Increment || action==Decrement)
//        {
////            trans.scale(1.+(1.-_lastScaleValue),1.);
////            setTransform(trans);
//            resetTransform();
//            trans = transform();
//            trans.rotate(_currentState);
//            qreal cosValue = cos((double)qAbs(value*M_PI/180));
////            qDebug() << action << value << cosValue << _lastScaleValue;
//            _lastScaleValue = cosValue;
////            return;
//            trans.scale(cosValue,1);
//        }
//        if(action == Reset)
//        {
////            qDebug() << action << _lastScaleValue;
//            resetTransform();
//            trans.rotate(_currentState);
//            _lastScaleValue = 1;
//        }
//        setTransform(trans);
//        childChangePos();
////        childRotate();
////        childScale();
//    }
//}


void DerrickItem::parentScaleChanged(qreal newValue)
{
//    qDebug() << _lastScaleValue << newValue;
    _lastScaleValue=newValue;

    QTransform trans;
    trans.rotate(_currentState);
    trans.scale(_lastScaleValue,1);
    setTransform(trans);

    emit scaledChanged(_lastScaleValue);
}


void DerrickItem::compareAndSetState(qreal newState)
{
    if(!qFuzzyCompare(100 + _currentState, 100 + newState))
    {
        // Значения не равны
        _currentState = newState;
//        resetTransform();
        QTransform trans;
        trans.rotate(_currentState);
        trans.scale(_lastScaleValue,1);
        setTransform(trans);
//        emit itemIsChanged(_type, Increment, _currentState);
        emit rotationChanged(_currentState);
    }
}
