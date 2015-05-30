#include "DecisionTreeNode.h"

#include "Core/Application.h"
#include "DecisionTreeEditor.h"

DecisionTreeNode::DecisionTreeNode(QGraphicsItem *parent) : TreeNode(parent)
{

}

DecisionTreeNode::~DecisionTreeNode()
{

}

void DecisionTreeNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void DecisionTreeNode::OnLinkBoxSelected(LinkBox *selected)
{
    ((DecisionTreeEditor*) Application::Get()->GetEditor())->OnLinkBoxSelected(selected);
}

void DecisionTreeNode::Remove()
{
    ((DecisionTreeEditor*) Application::Get()->GetEditor())->RemoveNode(this);
}

void DecisionTreeNode::InitialPropertyWidgets()
{
    Application::GetPropertyPanel()->Clear();
}

