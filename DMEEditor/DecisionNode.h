#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include "DecisionTreeNode.h"

class DecisionNode : public DecisionTreeNode
{
public:

    DecisionNode();
    ~DecisionNode();

    void SetLeftChild(DecisionTreeNode* leftChild);
    void SetRightChild(DecisionTreeNode* rightChild);

    void ReplaceChild(DecisionTreeNode* child, DecisionTreeNode* newNode);

private:
    QString conditionName;

    DecisionTreeNode* leftChild = nullptr;
    DecisionTreeNode* rightChild = nullptr;
};

#endif // DECISIONNODE_H
