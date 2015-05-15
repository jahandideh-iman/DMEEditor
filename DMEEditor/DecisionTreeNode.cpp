#include "DecisionTreeNode.h"
#include "Application.h"

DecisionTreeNode::DecisionTreeNode(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    ellipse = new QGraphicsEllipseItem(this);
    ellipse->setRect(QRect(-25,-25,50,50));
    textItem = new QGraphicsTextItem("?",this);
    textItem->setScale(1.5);

}


DecisionTreeNode::~DecisionTreeNode()
{

}

void DecisionTreeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;
    option;
    widget;
}

QRectF DecisionTreeNode::boundingRect() const
{
    return ellipse->boundingRect();
}

void DecisionTreeNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void DecisionTreeNode::InitialPropertyWidgets()
{
    Application::GetPropertyPanel()->Clear();
}

