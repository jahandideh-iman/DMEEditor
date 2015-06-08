#include "ActionNode.h"
#include "Core/Application.h"
#include <QDebug>

ActionNode::ActionNode(QGraphicsItem *parent) : DecisionTreeNode(parent)
{
    InitialToParentLinkBox();
    SetLinkBoxesLock(true);
    SetActionName("Action");
}

ActionNode::~ActionNode()
{

}

QString ActionNode::GetActionName()
{
    return GetNodeName();
}

void ActionNode::InitialPropertyWidgets()
{
    DecisionTreeNode::InitialPropertyWidgets();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Action Name", GetActionName(),this,SLOT(SetActionName(const QString& ))));
}

void ActionNode::RearrangeToParentLinkBox()
{
    GetToParentLinkBox()->setPos(0,-30);
}

void ActionNode::SetActionName(const QString& name)
{
    SetNodeName(name);
}
