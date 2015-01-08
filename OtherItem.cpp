#include "OtherItem.h"

OtherItem::OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=typeItem;
}


