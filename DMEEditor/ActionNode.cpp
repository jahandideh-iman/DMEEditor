#include "ActionNode.h"

ActionNode::ActionNode(PropertyPanel *propertyPanel) : DecisionTreeNode(propertyPanel)
{
    SetActionName("Default");
    ellipse->setBrush(QBrush(Qt::yellow));
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
    propertyPanel->AddProperty(new StringProperty("ActionName", actionName,this,SLOT(ActionNameChanged(const QString& ))));
}

void ActionNode::ActionNameChanged(const QString &value)
{
    SetActionName(value);
}

void ActionNode::SetActionName(QString value)
{
    actionName = value;
    textItem->setPlainText(actionName);

}


