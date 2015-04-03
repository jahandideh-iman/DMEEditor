#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "DecisionTreeNode.h"

class ActionNode : public DecisionTreeNode
{
public:
    ActionNode();
    ~ActionNode();

private:
    QString actionName;
};

#endif // ACTIONNODE_H

