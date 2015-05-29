#include "CompoundTask.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

CompoundTask::CompoundTask(CompoundTaskType type)
{
    toParentAttachBox = new AttachBox(AttachBox::Role_ToParent,this);
    toParentAttachBox->setY(-30);

    AddToChildAttachBox(true);

    this->type = type;

    if(type == t_SelectorTask)
        rect->setBrush(QBrush(Qt::blue));
    else if (type == t_SequenceTask)
        rect->setBrush(QBrush(Qt::red));
}


CompoundTaskType CompoundTask::StringToTaskType(QString str)
{
    if(str == "SequenceTask")
        return t_SequenceTask;
    if(str == "SelectorTask")
        return t_SelectorTask;
    return t_None;
}

CompoundTask::~CompoundTask()
{
    for(AttachBox* box : toChildAttachBoxes)
        delete box;
    delete toParentAttachBox;
}

void CompoundTask::ContributeToMenu(QMenu *menu)
{
    BehaviorTask::ContributeToMenu(menu);
    menu->addAction("Add Link", this, SLOT(AddRemoveableChildAttachBox()));
}

QString CompoundTask::GetTypeString()
{
    switch (type) {
    case t_SelectorTask:
        return "SelectorTask";
    case t_SequenceTask:
        return "SequenceTask";
    default:
        return "";
    }
}

QVector<BehaviorTask *> CompoundTask::GetChildren()
{
    QVector<BehaviorTask *> children;

    for(AttachBox* box : toChildAttachBoxes)
    {
        auto task = box->GetChildTask();
        if(task != nullptr)
            children.push_back(task);
    }

    return children;
}

AttachBox *CompoundTask::GetAnEmptyToChildAttachBox()
{
    for(AttachBox *box : toChildAttachBoxes)
        if(box->IsAttached() == false)
            return box;
    AddToChildAttachBox(true);
    return toChildAttachBoxes[toChildAttachBoxes.size()-1];
}

void CompoundTask::AddRemoveableChildAttachBox()
{
    AddToChildAttachBox(true);
}

