#include "FiniteStateMachineGraphicsScene.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <FiniteStateMachineEditor.h>
#include "StateNode.h"
#include "StateLink.h"
#include <QGraphicsEllipseItem>

FiniteStateMachineGraphicsScene::FiniteStateMachineGraphicsScene(FiniteStateMachineEditor *editor)
{
    this->editor = editor;

    connectionPlaceHolder = new QGraphicsLineItem();
    addItem(connectionPlaceHolder);
    connectionPlaceHolder->setVisible(false);
}

FiniteStateMachineGraphicsScene::~FiniteStateMachineGraphicsScene()
{

}

void FiniteStateMachineGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);

    QGraphicsItem *item =itemAt(event->scenePos(),QTransform());

    if(dynamic_cast<StateNode*> (item) != nullptr)
        ShowContextMenuForNode(event, dynamic_cast<StateNode*> (item));
    else if(dynamic_cast<StateLink*> (item) != nullptr )
        ShowContextMenuForLink(event,dynamic_cast<StateLink*> (item));
    else
        ShowContextMenu(event);
}

void FiniteStateMachineGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if(mouseEvent->button() == Qt::LeftButton)
    {
        if(isInConnectingState)
        {
            StateNode* node  = dynamic_cast<StateNode*> (itemAt(mouseEvent->scenePos(),QTransform()));
            if(node != nullptr)
                FinishConnectingNodeHelper(node);
        }
    }
    else if( mouseEvent->button() == Qt::RightButton)
    {
        if(isInConnectingState)
        {
            CancelConnectingNodeHelper();
        }
    }

}

void FiniteStateMachineGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if(isInConnectingState)
    {
        connectionPlaceHolder->setLine(QLineF(selectedNode->pos(), mouseEvent->scenePos()));
    }
}


void FiniteStateMachineGraphicsScene::ShowContextMenu(QGraphicsSceneContextMenuEvent *event)
{
    contexMenuPosition = event->scenePos();
    QMenu *menu=new QMenu();
    menu->addAction("Create State",this,SLOT(CreateNodeHelper()));
    menu->exec(event->screenPos());
}

void FiniteStateMachineGraphicsScene::ShowContextMenuForNode(QGraphicsSceneContextMenuEvent *event, StateNode *node)
{
    selectedNode = node;
    QMenu *menu=new QMenu();
    menu->addAction("Connect",this, SLOT(StartConnectingNodeHelper()));
    menu->addAction("Delete", this, SLOT(DeleteNodeHelper()));
    if(node->IsRoot() == false)
        menu->addAction("Set As Root", this, SLOT(SetRootNodeHelper()));
    menu->exec(event->screenPos());
}

void FiniteStateMachineGraphicsScene::ShowContextMenuForLink(QGraphicsSceneContextMenuEvent *event, StateLink *link)
{
    selectedLink = link;
    QMenu *menu=new QMenu();
    menu->addAction("Delete", this, SLOT(DeleteLinkHelper()));
    menu->exec(event->screenPos());
}

void FiniteStateMachineGraphicsScene::CreateNodeHelper()
{
    editor->CreateNode(contexMenuPosition);
}

void FiniteStateMachineGraphicsScene::DeleteNodeHelper()
{
    editor->DeleteNode(selectedNode);
}

void FiniteStateMachineGraphicsScene::StartConnectingNodeHelper()
{
    isInConnectingState = true;
    connectionPlaceHolder->setVisible(true);
    connectionPlaceHolder->setLine(QLineF(selectedNode->pos(),selectedNode->pos()));
    editor->StartConnectingNode(selectedNode);
}

void FiniteStateMachineGraphicsScene::FinishConnectingNodeHelper(StateNode* endNode)
{
    isInConnectingState = false;
    connectionPlaceHolder->setVisible(false);
    editor->FinishConnectingNode(endNode);
}

void FiniteStateMachineGraphicsScene::CancelConnectingNodeHelper()
{
    isInConnectingState = false;
    connectionPlaceHolder->setVisible(false);
    editor->CancelConnectingNode();
}

void FiniteStateMachineGraphicsScene::SetRootNodeHelper()
{
    editor->SetRootNode(selectedNode);
}

void FiniteStateMachineGraphicsScene::DeleteLinkHelper()
{
    editor->DeleteLink(selectedLink);
}
