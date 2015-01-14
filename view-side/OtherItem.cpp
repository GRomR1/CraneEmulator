#include "OtherItem.h"

using namespace Side;

OtherItem::OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent) :
    AbstractItem(renderer, parent)
{
    _type=typeItem;
}


