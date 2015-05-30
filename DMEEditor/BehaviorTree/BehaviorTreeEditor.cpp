#include "BehaviorTreeEditor.h"
#include "BehaviorTreeGraphicsScene.h"
#include "ActionTask.h"
#include "CompoundTask.h"

BehaviorTreeEditor::BehaviorTreeEditor()
{
    scene = new BehaviorTreeGraphicsScene(this);
    view->setScene(scene);

    InitialDummyRoot();
}

BehaviorTreeEditor::~BehaviorTreeEditor()
{
    for(auto task: tasks)
        delete task;
}

void BehaviorTreeEditor::CreateActionTask(QPointF pos)
{
    AddTask(new ActionTask(), pos);
}

void BehaviorTreeEditor::CreateSequenceTask(QPointF pos)
{
    AddTask(new CompoundTask(t_SequenceTask), pos);
}

void BehaviorTreeEditor::CreateSelectorTask(QPointF pos)
{
    AddTask(new CompoundTask(t_SelectorTask), pos);
}

void BehaviorTreeEditor::AddTask(BehaviorTask *task, QPointF pos)
{
    task->setPos(pos);
    scene->addItem(task);
    tasks.push_back(task);
}

void BehaviorTreeEditor::RemoveTask(BehaviorTask *task)
{
    tasks.removeAll(task);
    delete task;
}

void BehaviorTreeEditor::OnLinkBoxSelected(LinkBox* selectedBox)
{
    if(lastSelectedLinkBox != nullptr && lastSelectedLinkBox != selectedBox)
    {
        LinkTasks(lastSelectedLinkBox, selectedBox);
        SetInLinkingState(false);
    }
    else
    {
        lastSelectedLinkBox = selectedBox;
        SetInLinkingState(true);
    }
}

void BehaviorTreeEditor::CancelMouseTacking()
{
    SetInLinkingState(false);
}

void BehaviorTreeEditor::LinkTasks(LinkBox *start, LinkBox *end)
{
    Link *link;

    if(start->IsParent() && end->IsChild())
        link = new Link(start, end);
    else if(end->IsParent()&& start->IsChild())
        link = new Link(end, start);
    else
        return;

    scene->addItem(link);
}

void BehaviorTreeEditor::LinkTasks(BehaviorTask *parent, BehaviorTask *child)
{
    LinkTasks(parent->GetAnEmptyToChildAttachBox(), child->GetToParentLinkBox());
}

BehaviorTask *BehaviorTreeEditor::GetRoot()
{
    return dummyRoot->GetChild();
}

void BehaviorTreeEditor::SetRoot(BehaviorTask *root)
{
    LinkTasks(dummyRoot->GetToChildLinkBox(0), root->GetToParentLinkBox());
}

void BehaviorTreeEditor::SetInLinkingState(bool flag)
{
    if(flag == false)
    {
        lastSelectedLinkBox = nullptr;
        ((BehaviorTreeGraphicsScene*) scene)->StopMouseTracking();
    }
    else
        ((BehaviorTreeGraphicsScene*) scene)->StartMouseTracking(lastSelectedLinkBox);
}

void BehaviorTreeEditor::InitialDummyRoot()
{
    dummyRoot = new DummyRoot();
    AddTask(dummyRoot, QPointF(view->sceneRect().width()/2, 50));
    view->centerOn(dummyRoot);
}
