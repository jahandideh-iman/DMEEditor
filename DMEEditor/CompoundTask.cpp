#include "CompoundTask.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

CompoundTask::CompoundTask()
{
    parrentAttachBox = new AttachBox(AttachBox::Role_Parent,this);
    parrentAttachBox->setY(-30);

    AddChildAttachBox(true);
}

CompoundTask::~CompoundTask()
{
    for(AttachBox* box : childAttachBoxes)
        delete box;
    delete parrentAttachBox;
}

void CompoundTask::ContributeToMenu(QMenu *menu)
{
    BehaviorTask::ContributeToMenu(menu);
    menu->addAction("Add Link", this, SLOT(AddRemoveableChildAttachBox()));
}

void CompoundTask::AddRemoveableChildAttachBox()
{
    AddChildAttachBox(true);
}

