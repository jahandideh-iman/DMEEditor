#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode(PropertyPanel* propertyPanel,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    ellipse = new QGraphicsEllipseItem(this);
    ellipse->setRect(QRect(-25,-25,50,50));

    textItem = new QGraphicsTextItem("?",this);
    textItem->setScale(1.5);

    this->propertyPanel = propertyPanel;
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

void DecisionTreeNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void DecisionTreeNode::InitialPropertyWidgets()
{
    propertyPanel->Clear();
}

