#include "ActionNode.h"
#include "mainwindow.h"

ActionNode::ActionNode(QGraphicsItem *parent) : DecisionTreeNode(parent)
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
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("ActionName", actionName,this,SLOT(SetActionName(const QString& ))));
}


void ActionNode::SetActionName(const QString& value)
{
    actionName = value;
    textItem->setPlainText(actionName);

}


