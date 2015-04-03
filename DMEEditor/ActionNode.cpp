#include "ActionNode.h"

ActionNode::ActionNode()
{
    actionName = "DefaultAction";

    textItem->setPlainText(actionName);

    ellipse->setBrush(QBrush(Qt::yellow));
}

ActionNode::~ActionNode()
{

}


