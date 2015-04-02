#ifndef UNKOWNDECISIONTREENODE_H
#define UNKOWNDECISIONTREENODE_H

#include "Node.h"

class UnkownDecisionTreeNode : public Node
{
public:
    UnkownDecisionTreeNode();
    ~UnkownDecisionTreeNode();

private:
    QGraphicsTextItem* textItem = nullptr;
};

#endif // UNKOWNDECISIONTREENODE_H
