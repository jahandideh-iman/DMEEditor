#include "Node.h"

Node::Node(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    ellipse = new QGraphicsEllipseItem(this);
    ellipse->setRect(QRect(0,0,50,50));
    ellipse->setBrush(QBrush(Qt::blue));
}

Node::~Node()
{

}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF Node::boundingRect() const
{
    return ellipse->boundingRect();
}

