#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    ellipse = new QGraphicsEllipseItem(this);
    ellipse->setRect(QRect(0,0,50,50));

    textItem = new QGraphicsTextItem("?",this);
    textItem->setScale(1.5);
}


DecisionTreeNode::~DecisionTreeNode()
{

}

void DecisionTreeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF DecisionTreeNode::boundingRect() const
{
    return ellipse->boundingRect();
}

