#include "HookItem.h"

HookItem::HookItem(QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=Hook;
}

QVariant HookItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    emit signalItemChanged(change);
    return AbstractItem::itemChange(change, value);
}


//void HookItem::slotItemChanged(GraphicsItemChange change)
//{
////    qDebug() << "hook was changed" << change;
//    if(change == QGraphicsItem::ItemTransformHasChanged && scene())
//    {
//        qDebug() << "hook was scaled";
//        QTransform t = dynamic_cast<AbstractItem *>(sender())->transform();
//        QTransform tThis = transform();
//        qDebug() << t.isScaling();
//        qDebug() << t.m11() << tThis.m11();
//        qDebug() << t.m22() << tThis.m22();
//    }
//}

void HookItem::increment()
{
    emit itemIsChanged(_type, Increment, _currentState);
}

void HookItem::decrement()
{
    emit itemIsChanged(_type, Decrement, _currentState);
}

void HookItem::setCountSteps(int count)
{
    Q_UNUSED(count);
}


qreal HookItem::min() const
{
    return 0;
}

qreal HookItem::max() const
{
    return 0;
}
