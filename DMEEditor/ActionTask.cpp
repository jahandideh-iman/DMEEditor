#include "ActionTask.h"
#include "Application.h"
#include "PropertyPanel.h"
#include "StringProperty.h"

ActionTask::ActionTask()
{
    parrentAttachBox = new AttachBox(AttachBox::Role_Parent,this);
    parrentAttachBox->setY(-30);

    actionName = new QGraphicsTextItem(this);
    InitialProperties();
}

ActionTask::~ActionTask()
{
    delete actionName;

}

void ActionTask::SetActionName(const QString &name)
{
    actionName->setPlainText(name);
}

void ActionTask::InitialProperties()
{
    Application::GetPropertyPanel()->Clear();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("ActionName", GetActionName(),this,SLOT(SetActionName(const QString& ))));

}

QString ActionTask::GetActionName()
{
    return actionName->toPlainText();
}

void ActionTask::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    BehaviorTask::mouseDoubleClickEvent(event);
    InitialProperties();
}


