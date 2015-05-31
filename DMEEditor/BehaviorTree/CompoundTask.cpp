#include "CompoundTask.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

CompoundTask::CompoundTask()
{
    InitialToParentLinkBox();
    AddARemoveableToChildLinkBox();
}

CompoundTask::~CompoundTask()
{
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

void CompoundTask::RearrangeToParentLinkBox()
{
    GetToParentLinkBox()->setY(-30);
}

void CompoundTask::RearrangeToChildLinkBoxes()
{
    int xDistance = 15;
    int boxXPos = (toChildLinkBoxes.size()-1) / 2.0 * -xDistance;
    for(int i = 0 ; i < toChildLinkBoxes.size() ; ++i)
    {
        toChildLinkBoxes[i]->setPos(boxXPos, 30);
        boxXPos += xDistance;
    }
}

