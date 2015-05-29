#include "BehaviorTreeGraphicsScene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "BehaviorTreeEditor.h"
#include "AttachBox.h"
#include "ActionTask.h"
#include "Core/Application.h"
#include "Utilities/MenuContributer.h"

BehaviorTreeGraphicsScene::BehaviorTreeGraphicsScene(BehaviorTreeEditor *editor)
{
    this->editor = editor;

    attachmentPlaceHolder = new QGraphicsLineItem();
    addItem(attachmentPlaceHolder);
    attachmentPlaceHolder->setVisible(false);
}

BehaviorTreeGraphicsScene::~BehaviorTreeGraphicsScene()
{

}

void BehaviorTreeGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if(trackedItem != nullptr)
    {
        attachmentPlaceHolder->setLine(QLineF(trackedItem->mapToScene(0,0), mouseEvent->scenePos()));
    }
}

void BehaviorTreeGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Application::GetPropertyPanel()->Clear();
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void BehaviorTreeGraphicsScene::StartTracking(QGraphicsItem* item)
{
    trackedItem = item;
    attachmentPlaceHolder->setVisible(true);
}

void BehaviorTreeGraphicsScene::StopTracking()
{
    trackedItem = nullptr;
    attachmentPlaceHolder->setVisible(false);
}


void BehaviorTreeGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);
    auto item = itemAt(event->scenePos(),QTransform());
    QMenu menu;

    if (dynamic_cast<MenuContributer*> (item) != nullptr)
    {
        dynamic_cast<MenuContributer*> (item)->ContributeToMenu(&menu);
    }
    else
    {
        clickPosition = event->scenePos().toPoint();

        menu.addAction("Create Action Node",this, SLOT(CreateActionTaskHelper()));
        menu.addAction("Create Sequence Node", this, SLOT(CreateSequenceTaskHelper()));
        menu.addAction("Create Selector Node", this, SLOT(CreateSelectorTaskHelper()));
    }
    if(menu.actions().isEmpty() == false)
        menu.exec(event->screenPos());
}

void BehaviorTreeGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    if( mouseEvent->button() == Qt::RightButton)
        editor->CancelAttachment();
}

void BehaviorTreeGraphicsScene::CreateActionTaskHelper()
{
    editor->CreateActionTask(clickPosition);
}

void BehaviorTreeGraphicsScene::CreateSelectorTaskHelper()
{
    editor->CreateSelectorTask(clickPosition);
}

void BehaviorTreeGraphicsScene::CreateSequenceTaskHelper()
{
    editor->CreateSequenceTask(clickPosition);
}


