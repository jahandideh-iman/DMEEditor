#include "BehaviorTreeGraphicsScene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "BehaviorTreeEditor.h"
#include "AttachBox.h"
#include "ActionTask.h"

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
    if(isInAttachingState)
    {
        attachmentPlaceHolder->setLine(QLineF(selectedAttachBox->mapToScene(0,0), mouseEvent->scenePos()));
    }
}


void BehaviorTreeGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);

    QGraphicsItem *item =itemAt(event->scenePos(),QTransform());
    if( dynamic_cast<AttachBox*> (item) != nullptr)
    {
        selectedAttachBox = dynamic_cast<AttachBox*> (item);
        QMenu *menu = new QMenu();
        menu->addAction("Attach", this, SLOT(StartAttachingHelper()));
        menu->exec(event->screenPos());
    }
    else
    {
        QMenu *menu=new QMenu();
        menu->addAction("Create Action Node",this, SLOT(CreateActionTaskHelper()));
        menu->addAction("Create Sequence Node");
        menu->addAction("Create Selector Node");
        menu->exec(event->screenPos());
    }

}

void BehaviorTreeGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if(mouseEvent->button() == Qt::LeftButton)
    {
        if(isInAttachingState)
        {
            AttachBox* box  = dynamic_cast<AttachBox*> (itemAt(mouseEvent->scenePos(),QTransform()));
            if(box != nullptr)
                FinishAttachingHelper(box);
        }
    }
    else if( mouseEvent->button() == Qt::RightButton)
        if(isInAttachingState)
            CancelAttachingHelper();

}

void BehaviorTreeGraphicsScene::CreateActionTaskHelper()
{
    editor->CreateActionTask(QPoint(100,100));
}

void BehaviorTreeGraphicsScene::StartAttachingHelper()
{
    isInAttachingState = true;
    attachmentPlaceHolder->setVisible(true);
    attachmentPlaceHolder->setLine(QLineF(selectedAttachBox->mapToScene(0,0),selectedAttachBox->mapToScene(0,0)));
}

void BehaviorTreeGraphicsScene::CancelAttachingHelper()
{
    isInAttachingState = false;
    attachmentPlaceHolder->setVisible(false);
}

void BehaviorTreeGraphicsScene::FinishAttachingHelper(AttachBox *box)
{
    editor->AttachTasks(selectedAttachBox, box);
    isInAttachingState = false;
    attachmentPlaceHolder->setVisible(false);
}


