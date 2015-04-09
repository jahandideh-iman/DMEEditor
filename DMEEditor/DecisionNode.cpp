#include "DecisionNode.h"
#include <QPainter>

DecisionNode::DecisionNode(PropertyPanel *propertyPanel) : DecisionTreeNode(propertyPanel)
{
    SetConditionName("DefaultCondition");
    ellipse->setBrush(QBrush(Qt::gray));
}


DecisionNode::~DecisionNode()
{
    delete rightChild;
    delete leftChild;
}

void DecisionNode::SetLeftChild(DecisionTreeNode *leftChild)
{
    this->leftChild = leftChild;
}

void DecisionNode::SetRightChild(DecisionTreeNode *rightChild)
{
    this->rightChild = rightChild;
}

void DecisionNode::ReplaceChild(DecisionTreeNode *child, DecisionTreeNode *newNode)
{
    if(rightChild == child)
        SetRightChild(newNode);
    else if( leftChild == child)
        SetLeftChild(newNode);
}

void DecisionNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DecisionTreeNode::paint(painter,option,widget);

    QPointF leftChildRelativePos = leftChild->pos() - pos();
    QPointF rightChildRelativePos = rightChild->pos() - pos();

    painter->drawLine(QPoint(0,0), leftChildRelativePos);
    painter->drawLine(QPoint(0,0), rightChildRelativePos);

    painter->drawText(leftChildRelativePos/2,"False");
    painter->drawText(rightChildRelativePos/2,"True");
}

void DecisionNode::InitialPropertyWidgets()
{
    DecisionTreeNode::InitialPropertyWidgets();
    propertyPanel->AddProperty(new StringProperty("ConditionName", conditionName,this,SLOT(ConditionNameChanged(const QString& ))));
}


void DecisionNode::ConditionNameChanged(const QString &value)
{
    SetConditionName(value);
}

void DecisionNode::SetConditionName(QString value)
{
    conditionName = value;
    textItem->setPlainText(conditionName);
}

