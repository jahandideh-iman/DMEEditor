#include "DecisionNode.h"
#include <QPainter>
#include "Core/Application.h"


DecisionNode::DecisionNode(QGraphicsItem *parent) : DecisionTreeNode(parent)
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

DecisionTreeNode *DecisionNode::GetLeftChild()
{
    return leftChild;
}

DecisionTreeNode *DecisionNode::GetRightChild()
{
    return rightChild;
}

QString DecisionNode::GetConditionName()
{
    return conditionName;
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
    Application::GetPropertyPanel()->AddProperty(new StringProperty("ConditionName", conditionName,this,SLOT(SetConditionName(const QString& ))));
}


void DecisionNode::SetConditionName(const QString &value)
{
    conditionName = value;
    textItem->setPlainText(conditionName);
}

