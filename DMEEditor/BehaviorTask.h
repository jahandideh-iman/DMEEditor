#ifndef BEHAVIORTASK_H
#define BEHAVIORTASK_H

#include <QGraphicsItem>
#include "AttachBox.h"

class BehaviorTask : public QGraphicsItem
{
public:
    BehaviorTask();
    ~BehaviorTask();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

protected:
    QGraphicsRectItem *rect = nullptr;

    AttachBox *parrentAttachBox = nullptr;
    AttachBox *childAttachBox = nullptr;
};

#endif // BEHAVIORTASK_H
