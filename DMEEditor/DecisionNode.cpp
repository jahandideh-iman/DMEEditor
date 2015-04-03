#include "DecisionNode.h"

DecisionNode::DecisionNode()
{
    conditionName = "DefaultCondition";
    textItem->setPlainText(conditionName);

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

