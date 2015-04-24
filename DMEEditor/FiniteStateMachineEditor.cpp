#include "FiniteStateMachineEditor.h"
#include "FiniteStateMachineGraphicsScene.h"
#include "StateNode.h"
#include "StateLink.h"
#include <QFile>
#include <QQueue>
#include <QVector>

FiniteStateMachineEditor::FiniteStateMachineEditor()
{
    scene = new FiniteStateMachineGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setSceneRect(0,0,1000,1000);
    view->setMouseTracking(true);

    IOManager = new FiniteStateMachineIOManager(this);

}

FiniteStateMachineEditor::~FiniteStateMachineEditor()
{

}

QGraphicsView *FiniteStateMachineEditor::GetView() const
{
    return view;
}

void FiniteStateMachineEditor::SaveToFile(QString &fileName)
{
    IOManager->SaveTo(fileName);
}

void FiniteStateMachineEditor::OpenFromFile(QString &fileName)
{
    IOManager->ReadFrom(fileName);
}

StateNode *FiniteStateMachineEditor::GetRootNode()
{
    return rootNode;
}

void FiniteStateMachineEditor::AddNode(StateNode *node)
{
    scene->addItem(node);

    if(rootNode == nullptr)
        SetRootNode(node);
}

void FiniteStateMachineEditor::AddLink(StateLink *link)
{
    scene->addItem(link);
}

void FiniteStateMachineEditor::DeleteLink(StateLink *link)
{
    scene->removeItem(link);
    delete link;
}


void FiniteStateMachineEditor::CreateNode(QPointF pos)
{
    StateNode * node = new StateNode();
    node->setPos(pos);

    AddNode(node);
}

void FiniteStateMachineEditor::DeleteNode(StateNode *node)
{
    auto inLinks = node->GetInLinks();
    for( auto link : inLinks)
        DeleteLink(link);

    auto outLinks = node->GetOutLinks();
    for( auto link : outLinks)
        DeleteLink(link);

    if(rootNode == node)
        rootNode = nullptr;
    delete node;
}

void FiniteStateMachineEditor::StartConnectingNode(StateNode *node)
{
    connectionStartNode = node;
}

void FiniteStateMachineEditor::FinishConnectingNode(StateNode *endNode)
{
    if( connectionStartNode != endNode)
        AddLink( new StateLink(connectionStartNode,endNode));

    connectionStartNode = nullptr;
}

void FiniteStateMachineEditor::CancelConnectingNode()
{
    connectionStartNode = nullptr;
}

void FiniteStateMachineEditor::SetRootNode(StateNode *node)
{
    if(rootNode != nullptr)
        rootNode->SetRootFlag(false);

    node->SetRootFlag(true);
    rootNode = node;
}

