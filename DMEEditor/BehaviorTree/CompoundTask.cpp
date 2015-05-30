#include "CompoundTask.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

CompoundTask::CompoundTask(CompoundTaskType type)
{
    InitialToParentLinkBox();

    AddARemoveableToChildLinkBox();

    this->type = type;

//    if(type == t_SelectorTask)
//        rect->setBrush(QBrush(Qt::blue));
//    else if (type == t_SequenceTask)
//        rect->setBrush(QBrush(Qt::red));
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

    for(LinkBox * box : toChildLinkBoxes)
    {
        auto task = dynamic_cast<BehaviorTask*> (box->GetChildNode());
        if(task != nullptr)
            children.push_back(task);
    }

    return children;
}

LinkBox *CompoundTask::GetAnEmptyToChildAttachBox()
{
    for(LinkBox *box : toChildLinkBoxes)
        if(box->IsLinked() == false)
            return box;
    AddARemoveableToChildLinkBox();
    return toChildLinkBoxes[toChildLinkBoxes.size()-1];
}
