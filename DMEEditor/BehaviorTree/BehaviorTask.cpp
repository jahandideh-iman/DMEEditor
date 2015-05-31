#include "BehaviorTask.h"
#include "Core/Application.h"
#include "BehaviorTreeEditor.h"

BehaviorTask::BehaviorTask()
{
}

BehaviorTask::~BehaviorTask()
{

}

void BehaviorTask::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void BehaviorTask::OnLinkBoxSelected(LinkBox *selected)
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->OnLinkBoxSelected(selected);
}

void BehaviorTask::Remove()
{
   ((BehaviorTreeEditor*) Application::Get()->GetEditor())->RemoveTask(this);
}

void BehaviorTask::InitialPropertyWidgets()
{

}
