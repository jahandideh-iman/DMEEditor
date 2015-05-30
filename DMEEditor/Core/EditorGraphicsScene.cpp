#include "EditorGraphicsScene.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Utilities/MenuContributer.h"
#include "Editor.h"

EditorGraphicsScene::EditorGraphicsScene(Editor *editor)
{
    this->editor = editor;

    mouseTrackingLine = new QGraphicsLineItem();
    addItem(mouseTrackingLine);
    mouseTrackingLine->setVisible(false);
}

EditorGraphicsScene::~EditorGraphicsScene()
{
    delete mouseTrackingLine;
}

void EditorGraphicsScene::StartMouseTracking(QGraphicsItem *startingItem)
{
    mouseTrackingStartingItem = startingItem;
    mouseTrackingLine->setVisible(true);
    UpdateMouseTrackingLine(startingItem->scenePos());
}

void EditorGraphicsScene::StopMouseTracking()
{
    mouseTrackingStartingItem = nullptr;
    mouseTrackingLine->setVisible(false);
}

void EditorGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);

    if(IsTrackingMouse())
    {
         editor->CancelMouseTacking();
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
        ContributeToMenu(&menu);
    }

    if(menu.actions().isEmpty() == false)
        menu.exec(event->screenPos());
}

void EditorGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if(IsTrackingMouse())
        UpdateMouseTrackingLine(mouseEvent->scenePos());
}

bool EditorGraphicsScene::IsTrackingMouse()
{
    return mouseTrackingStartingItem != nullptr;
}

void EditorGraphicsScene::UpdateMouseTrackingLine(QPointF scenePos)
{
    mouseTrackingLine->setLine(QLineF(mouseTrackingStartingItem->mapToScene(0,0), scenePos));
}
