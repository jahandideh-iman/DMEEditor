#include "ActionTask.h"
#include "Core/Application.h"
#include "Utilities/PropertyPanel.h"
#include "Utilities/StringProperty.h"

ActionTask::ActionTask()
{
    InitialToParentLinkBox();
    SetLinkBoxesLock(true);
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

LinkBox *ActionTask::GetAnEmptyToChildAttachBox()
{
    return nullptr;
}


