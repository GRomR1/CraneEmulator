#include "Top_OtherItem.h"

using namespace Top;

OtherItem::OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=typeItem;
}


