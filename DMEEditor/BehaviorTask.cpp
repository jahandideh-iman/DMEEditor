#include "BehaviorTask.h"

BehaviorTask::BehaviorTask()
{
    rect = new QGraphicsRectItem(QRect(-30,-30,60,60),this);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

BehaviorTask::~BehaviorTask()
{

}

void BehaviorTask::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;
    option;
    widget;
}

QRectF BehaviorTask::boundingRect() const
{
    return rect->boundingRect();
}
