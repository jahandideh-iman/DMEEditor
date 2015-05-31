#include "ActionTask.h"
#include "Core/Application.h"
#include "Utilities/PropertyPanel.h"
#include "Utilities/StringProperty.h"

ActionTask::ActionTask()
{
    InitialToParentLinkBox();
    SetLinkBoxesLock(true);

    SetActionName("Action");
}

ActionTask::~ActionTask()
{
}

void ActionTask::SetActionName(const QString &name)
{
    SetNodeName(name);
}

QString ActionTask::GetActionName()
{
    return GetNodeName();
}

void ActionTask::InitialPropertyWidgets()
{
    Application::GetPropertyPanel()->Clear();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("ActionName", GetActionName(),this,SLOT(SetActionName(const QString& ))));
}

void ActionTask::RearrangeToParentLinkBox()
{
    GetToParentLinkBox()->setY(-30);
}

LinkBox *ActionTask::GetAnEmptyToChildAttachBox()
{
    return nullptr;
}


