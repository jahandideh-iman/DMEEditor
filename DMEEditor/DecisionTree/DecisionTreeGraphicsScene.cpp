#include "DecisionTreeGraphicsScene.h"
#include "DecisionTreeEditor.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include "Utilities/MenuContributer.h"
#include "DecisionTreeNode.h"

DecisionTreeGraphicsScene::DecisionTreeGraphicsScene(DecisionTreeEditor *editor)
{
    this->editor = editor;

    mouseTrackingLine = new QGraphicsLineItem();
    addItem(mouseTrackingLine);
    mouseTrackingLine->setVisible(false);
}

DecisionTreeGraphicsScene::~DecisionTreeGraphicsScene()
{

}

void DecisionTreeGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);

    if(IsTrackingMouse())
    {
         editor->CancelLinking();
         return;
    }

    auto item = itemAt(event->scenePos(),QTransform());
    QMenu menu;

    if (dynamic_cast<MenuContributer*> (item) != nullptr)
    {
        dynamic_cast<MenuContributer*> (item)->ContributeToMenu(&menu);
    }
    else
    {
        clickPosition = event->scenePos();

        menu.addAction("Create Action Node",this, SLOT(CreateActionNodeHelper()));
        menu.addAction("Create Decision Node", this, SLOT(CreateDicisionNodeHelper()));
    }

    if(menu.actions().isEmpty() == false)
        menu.exec(event->screenPos());
}

void DecisionTreeGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if(IsTrackingMouse())
        UpdateMouseTrackingLine(mouseEvent->scenePos());
}

void DecisionTreeGraphicsScene::StartMouseTracking(QGraphicsItem *startingItem)
{
    mouseTrackingStartingItem = startingItem;
    mouseTrackingLine->setVisible(true);
    UpdateMouseTrackingLine(startingItem->scenePos());
}

void DecisionTreeGraphicsScene::StopMouseTracking()
{
    mouseTrackingStartingItem = nullptr;
    mouseTrackingLine->setVisible(false);
}

void DecisionTreeGraphicsScene::CreateActionNodeHelper()
{
    editor->CreateActionNode(clickPosition);
}

void DecisionTreeGraphicsScene::CreateDicisionNodeHelper()
{
    editor->CreateDecisionNode(clickPosition);
}

bool DecisionTreeGraphicsScene::IsTrackingMouse()
{
    return mouseTrackingStartingItem != nullptr;
}

void DecisionTreeGraphicsScene::UpdateMouseTrackingLine(QPointF scenePos)
{
    mouseTrackingLine->setLine(QLineF(mouseTrackingStartingItem->mapToScene(0,0), scenePos));
}

