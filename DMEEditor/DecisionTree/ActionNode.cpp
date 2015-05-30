#include "ActionNode.h"
#include "Core/Application.h"
#include <QDebug>

ActionNode::ActionNode(QGraphicsItem *parent) : DecisionTreeNode(parent)
{
    CreateToParentLinkBox();
    //SetShape(new QGraphicsRectItem());
    SetLinkBoxesLock(true);
    SetActionName("Action");
}

ActionNode::~ActionNode()
{

}

QString ActionNode::GetActionName()
{
    return actionName;
}

void ActionNode::InitialPropertyWidgets()
{
    DecisionTreeNode::InitialPropertyWidgets();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("ActionName", actionName,this,SLOT(SetActionName(const QString& ))));
}

void ActionNode::RearrangeToParentLinkBox()
{
    GetToParentLinkBox()->setPos(0,-30);
}


void ActionNode::SetActionName(const QString& value)
{
    actionName = value;
    SetNodeName(actionName);
}


