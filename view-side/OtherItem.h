#ifndef OTHERITEM_H
#define OTHERITEM_H

#include "../AbstractItem.h"
namespace Side {

class OtherItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent = 0);
};

}

#endif // OTHERITEM_H
