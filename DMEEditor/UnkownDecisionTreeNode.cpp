#include "UnkownDecisionTreeNode.h"

UnkownDecisionTreeNode::UnkownDecisionTreeNode()
{
    ellipse->setBrush(QBrush(Qt::white));
    textItem = new QGraphicsTextItem("?",this);
    textItem->setScale(2.5);
}

UnkownDecisionTreeNode::~UnkownDecisionTreeNode()
{

}

