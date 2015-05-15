#include "BehaviorTreeEditor.h"
#include "BehaviorTreeGraphicsScene.h"
#include "ActionTask.h"
#include "AttachBox.h"
#include "Attachment.h"
#include "CompoundTask.h"

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
    for(auto task: tasks)
        delete task;

}

void BehaviorTreeEditor::CreateActionTask(QPoint pos)
{
    AddTask(new ActionTask(), pos);
}

void BehaviorTreeEditor::CreateSequenceTask(QPoint pos)
{
    AddTask(new CompoundTask(), pos);
}

void BehaviorTreeEditor::CreateSelectorTask(QPoint pos)
{
    AddTask(new CompoundTask(), pos);
}


void BehaviorTreeEditor::AddTask(BehaviorTask *task, QPoint pos)
{
    task->setPos(pos);
    scene->addItem(task);
    tasks.push_back(task);
}


void BehaviorTreeEditor::RemoveTask(BehaviorTask *task)
{
    scene->removeItem(task);
    delete task;
}

void BehaviorTreeEditor::AttachBoxSelected(AttachBox *attachBox)
{
    if(lastAttachBox != nullptr && attachBox != lastAttachBox)
    {
        AttachTasks(lastAttachBox, attachBox);
        SetInAttachingState(false);
    }
    else
    {
        lastAttachBox = attachBox;
        SetInAttachingState(true);
    }
}

void BehaviorTreeEditor::CancelAttachment()
{
    SetInAttachingState(false);
}

void BehaviorTreeEditor::AttachTasks(AttachBox *start, AttachBox *end)
{
    Attachment *attachment;
    if(start->GetRole() == AttachBox::Role_Parent && end->GetRole() == AttachBox::Role_Child )
        attachment = new Attachment(start, end);
    else if(end->GetRole() == AttachBox::Role_Parent && start->GetRole() == AttachBox::Role_Child )
        attachment = new Attachment(end, start);
    else
        return;

    attachment->setZValue(start->zValue()-1);
    scene->addItem(attachment);
}

void BehaviorTreeEditor::Detach(Attachment *attachment)
{
    scene->removeItem(attachment);
    delete attachment;
}

void BehaviorTreeEditor::SetInAttachingState(bool flag)
{
    if(flag == false)
    {
        lastAttachBox = nullptr;
        ((BehaviorTreeGraphicsScene*) scene)->StopTracking();

    }
    else
        ((BehaviorTreeGraphicsScene*) scene)->StartTracking(lastAttachBox);
}
