#include "UndeterminedDecisionTreeNode.h"
#include <QGraphicsSceneContextMenuEvent>
#include "DecisionTreeEditor.h"



UndeterminedDecisionTreeNode::UndeterminedDecisionTreeNode(DecisionTreeEditor* editor, DecisionNode *parentNode)
{
    this->parentNode = parentNode;
    this->editor = editor;
}

UndeterminedDecisionTreeNode::~UndeterminedDecisionTreeNode()
{

}

void UndeterminedDecisionTreeNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    qDebug("UnkownDecisionTreeNode::contextMenuEvent");
    QMenu *menu=new QMenu();
    menu->addAction("Convert to Decsion Node",this,SLOT(ConvertToDecisionNode()));
    menu->addAction("Convert to Action Node",this,SLOT(ConvertToActionNode()));
    menu->exec(event->screenPos());
}

DecisionNode *UndeterminedDecisionTreeNode::getParentNode()
{
    return parentNode;
}

void UndeterminedDecisionTreeNode::ConvertToActionNode()
{
    editor->ConvertToActionNode(this);
}

void UndeterminedDecisionTreeNode::ConvertToDecisionNode()
{
    editor->ConvertToDecisionNode(this);
}



