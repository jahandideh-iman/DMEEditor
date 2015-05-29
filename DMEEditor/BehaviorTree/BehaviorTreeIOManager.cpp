#include "BehaviorTreeIOManager.h"
#include "BehaviorTreeEditor.h"
#include "ActionTask.h"
#include "CompoundTask.h"


BehaviorTreeIOManager::BehaviorTreeIOManager()
{

}

BehaviorTreeIOManager::~BehaviorTreeIOManager()
{

}

bool BehaviorTreeIOManager::IsCompatibleWith(Editor *editor)
{
    return dynamic_cast<BehaviorTreeEditor*> (editor) != nullptr;
}

void BehaviorTreeIOManager::Save(Editor *editor)
{
    this->editor = dynamic_cast<BehaviorTreeEditor* > (editor);
    SaveTask(this->editor->GetRoot());
}

QString BehaviorTreeIOManager::GetType()
{
    return "BehaviorTree";
}

void BehaviorTreeIOManager::SaveTask(BehaviorTask *task, int depth)
{
    if(task == nullptr)
        return;

    QString tabs = QString(depth, '\t');

    QString xPos = "XPos=\"" +QString::number(task->pos().x()) + "\" ";
    QString yPos = "YPos=\"" +QString::number(task->pos().y()) + "\" ";

    if(dynamic_cast<CompoundTask*>(task) != nullptr)
    {
        auto compoundTask = dynamic_cast<CompoundTask*>(task);

        WriteToFile( tabs + "<Task type=\""+ compoundTask->GetTypeString() +"\" " + xPos + yPos +" > \n");

        for(auto child : compoundTask->GetChildren())
        {
            WriteToFile( tabs + "\t" + "<Child>" + "\n");
            SaveTask(child, depth+2);
            WriteToFile( tabs + "\t" + "</Child>" + "\n");
        }

        WriteToFile( tabs + "</Task> \n");
    }
    else if(dynamic_cast<ActionTask*>(task)!= nullptr)
    {
        auto actionTask = dynamic_cast<ActionTask*>(task);
        WriteToFile( tabs + "<Task type=\"ActionTask\" " + xPos + yPos + "> \n");
        WriteToFile(tabs + "\t<Action>" + actionTask->GetActionName() + "</Action> \n");
        WriteToFile( tabs + "</Task> \n");
    }
}

void BehaviorTreeIOManager::Parse(IOManager::XMLNode *rootXMLNode, Editor *editor_)
{
    editor = dynamic_cast<BehaviorTreeEditor*> (editor_);
    editor->SetRoot(ExtractTask(rootXMLNode->first_node("Task")));
}


BehaviorTask *BehaviorTreeIOManager::ExtractTask(IOManager::XMLNode *xmlNode, BehaviorTask *parent)
{
    if (xmlNode == nullptr)
        return nullptr;

    QString taskType = GetTaskType(xmlNode);

    if (taskType == "ActionTask")
        return ExtractActionTask(xmlNode, parent);
    else if (taskType == "SequenceTask" || taskType == "SelectorTask")
        return ExtractCompoundTask(xmlNode, parent);

    return nullptr;
}

BehaviorTask *BehaviorTreeIOManager::ExtractActionTask(IOManager::XMLNode *xmlNode, BehaviorTask *parent)
{
    auto actionTask = new ActionTask();
    XMLNode* actionXMLNode = xmlNode->first_node("Action");
    if (actionXMLNode != nullptr)
        actionTask->SetActionName(actionXMLNode->value());

    ParseTaskPosition(actionTask, xmlNode);
    editor->AddTask(actionTask, actionTask->pos().toPoint());
    if(parent != nullptr)
        editor->AttachTasks(parent, actionTask);
    return actionTask;
}

BehaviorTask *BehaviorTreeIOManager::ExtractCompoundTask(IOManager::XMLNode *xmlNode, BehaviorTask *parent)
{
    CompoundTaskType type = CompoundTask::StringToTaskType(GetTaskType(xmlNode));
    auto compoundTask = new CompoundTask(type);
    ParseTaskPosition(compoundTask, xmlNode);

    editor->AddTask(compoundTask, compoundTask->pos().toPoint());

    auto childXMLNode = xmlNode->first_node("Child");
    while (childXMLNode != nullptr)
    {
        editor->AttachTasks(compoundTask, ExtractTask(childXMLNode->first_node("Task")));
        childXMLNode = childXMLNode->next_sibling("Child");
    }

    if(parent != nullptr)
        editor->AttachTasks(parent, compoundTask);

    return compoundTask;
}

QString BehaviorTreeIOManager::GetTaskType(IOManager::XMLNode *xmlNode)
{
    return xmlNode->first_attribute("type")->value();
}

void BehaviorTreeIOManager::ParseTaskPosition(BehaviorTask *task, IOManager::XMLNode *xmlNode)
{
    float xPos = QString(xmlNode->first_attribute("XPos")->value()).toFloat();
    float yPos = QString(xmlNode->first_attribute("YPos")->value()).toFloat();
    task->setPos(xPos,yPos);
}