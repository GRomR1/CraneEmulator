#ifndef OTHERITEMTOP_H
#define OTHERITEMTOP_H

#include "../AbstractItem.h"
namespace Top {

class OtherItem : public AbstractItem
{
    Q_OBJECT
public:
    explicit OtherItem(TypeItem typeItem, QSvgRenderer *renderer, QGraphicsItem *parent = 0);
};

}

#endif // OTHERITEMTOP_H
