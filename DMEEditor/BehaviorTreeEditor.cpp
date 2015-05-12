#include "BehaviorTreeEditor.h"
#include "BehaviorTreeGraphicsScene.h"
#include "ActionTask.h"
#include "AttachBox.h"
#include "Attachment.h"

BehaviorTreeEditor::BehaviorTreeEditor()
{
    scene = new BehaviorTreeGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setSceneRect(0,0,1000,1000);
    view->setMouseTracking(true);

    root = new RootTask();
    root->setPos(500,50);
    scene->addItem(root);

}

BehaviorTreeEditor::~BehaviorTreeEditor()
{

}

void BehaviorTreeEditor::CreateActionTask(QPoint pos)
{
    auto actionTask = new ActionTask();
    actionTask->setPos(pos);
    scene->addItem(actionTask);
}

void BehaviorTreeEditor::AttachTasks(AttachBox *box1, AttachBox *box2)
{
    Attachment *attachment;
    if(box1->GetRole() == AttachBox::Role_Parent && box2->GetRole() == AttachBox::Role_Child )
        attachment = new Attachment(box1, box2);
    else if(box2->GetRole() == AttachBox::Role_Parent && box1->GetRole() == AttachBox::Role_Child )
        attachment = new Attachment(box2, box1);
    else
        return;

    scene->addItem(attachment);
}

