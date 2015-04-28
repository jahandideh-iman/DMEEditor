#include "FiniteStateMachineIOManager.h"
#include <QFile>
#include "StateNode.h"
#include "StateTransition.h"
#include "FiniteStateMachineEditor.h"

FiniteStateMachineIOManager::FiniteStateMachineIOManager()
{
}

FiniteStateMachineIOManager::~FiniteStateMachineIOManager()
{

}

void FiniteStateMachineIOManager::Save(Editor *editor_)
{
    this->editor = dynamic_cast<FiniteStateMachineEditor*>(editor_);

    SaveStates();
    SaveTransitions();
    SaveRoot();
}

void FiniteStateMachineIOManager::SaveStates()
{
    WriteToFile("   <States>\n");

    auto states = editor->GetStates();
    for(StateNode* state : states)
    {
        QString xPos = "XPos=\"" +QString::number(state->pos().x()) + "\"";
        QString yPos = "YPos=\"" +QString::number(state->pos().y()) + "\"";
        WriteToFile("       <State " + xPos +" "+ yPos + " >\n");
        WriteToFile("           <Name>" + state->GetStateName()+"</Name>\n");
        WriteToFile("           <UpdateAction>" + state->GetUpdateActionName()+"</UpdateAction>\n");
        WriteToFile("           <EntryAction>" + state->GetEntryActionName()+"</EntryAction>\n");
        WriteToFile("           <ExitAction>" + state->GetExitActionName()+"</ExitAction>\n");
        WriteToFile("       </State>\n");
    }
    WriteToFile("   </States>\n");
}

void FiniteStateMachineIOManager::SaveTransitions()
{
    WriteToFile("   <Transitions>\n");

    auto traversal = editor->GetStates();
    for(auto state : traversal)
    {
        for(auto l : state->GetOutLinks())
        {
            WriteToFile("       <Transition>\n");
            WriteToFile("           <From>" + l->GetStartNode()->GetStateName()+"</From>\n");
            WriteToFile("           <To>" + l->GetEndNode()->GetStateName()+"</To>\n");
            WriteToFile("           <Condition>" + l->GetConditionName()+"</Condition>\n");
            WriteToFile("       </Transition>\n");
        }
    }
    WriteToFile("    </Transitions>\n");
}

void FiniteStateMachineIOManager::SaveRoot()
{
    if(editor->GetRootState() == nullptr)
        return;
    WriteToFile(("  <InitialState>" + editor->GetRootState()->GetStateName()+"</InitialState>\n").toStdString().c_str());
}

void FiniteStateMachineIOManager::Parse(IOManager::XMLNode *rootXMLNode, Editor *editor)
{
    this->editor = dynamic_cast<FiniteStateMachineEditor*> (editor);

    ParseStates(rootXMLNode->first_node("States"));
    ParseTransitions(rootXMLNode->first_node("Transitions"));
    ParseInitialState(rootXMLNode->first_node("InitialState"));
}

void FiniteStateMachineIOManager::ParseStates(FiniteStateMachineIOManager::XMLNode *statesXMLNode)
{
    if (statesXMLNode == nullptr)
        return;

    for (XMLNode* stateXMLNode = statesXMLNode->first_node("State");
        stateXMLNode; stateXMLNode = stateXMLNode->next_sibling("State"))
        ParseState(stateXMLNode);
}

void FiniteStateMachineIOManager::ParseState(FiniteStateMachineIOManager::XMLNode *stateXMLNode)
{
    QString stateName = stateXMLNode->first_node("Name")->value();
    auto node = new StateNode(stateName);
    parsedStatesMap.insert(stateName, node);

    ParseStatePosition(node, stateXMLNode);
    ParseStateUpdateAction(node, stateXMLNode->first_node("UpdateAction"));
    ParseStateEntryAction(node, stateXMLNode->first_node("EntryAction"));
    ParseStateExitAction(node, stateXMLNode->first_node("ExitAction"));
    editor->AddState(node);
}

void FiniteStateMachineIOManager::ParseStatePosition(StateNode *node, XMLNode *stateXMLNode)
{
    float xPos = QString(stateXMLNode->first_attribute("XPos")->value()).toFloat();
    float yPos = QString(stateXMLNode->first_attribute("YPos")->value()).toFloat();
    node->setPos(xPos,yPos);
}

void FiniteStateMachineIOManager::ParseStateEntryAction(StateNode *node, XMLNode *entryActionXMLNode)
{
    if(entryActionXMLNode != nullptr)
        node->SetEntryActionName(entryActionXMLNode->value());
}

void FiniteStateMachineIOManager::ParseStateUpdateAction(StateNode *node, XMLNode *updateActionXMLNode)
{
    if(updateActionXMLNode != nullptr)
        node->SetUpdateActionName(updateActionXMLNode->value());
}

void FiniteStateMachineIOManager::ParseStateExitAction(StateNode *node, XMLNode *exitActionXMLNode)
{
    if(exitActionXMLNode != nullptr)
        node->SetExitActionName(exitActionXMLNode->value());
}

void FiniteStateMachineIOManager::ParseTransitions(FiniteStateMachineIOManager::XMLNode *transitionsXMLNode)
{
    if(transitionsXMLNode == nullptr)
        return;

    for (XMLNode *transitionNode = transitionsXMLNode->first_node("Transition");
        transitionNode; transitionNode = transitionNode->next_sibling("Transition"))
        ParseTransition(transitionNode);
}

void FiniteStateMachineIOManager::ParseTransition(FiniteStateMachineIOManager::XMLNode *transitionXMLNode)
{
    QString fromStateNode = transitionXMLNode->first_node("From")->value();
    QString toStateNode = transitionXMLNode->first_node("To")->value();
    QString condition = transitionXMLNode->first_node("Condition")->value();

    StateTransition* transition = new StateTransition(parsedStatesMap[fromStateNode], parsedStatesMap[toStateNode], condition);
    editor->AddTransition(transition);
}

void FiniteStateMachineIOManager::ParseInitialState(FiniteStateMachineIOManager::XMLNode *initalStateXMLNode)
{
    if(initalStateXMLNode == nullptr)
        return;
    editor->SetRootState(parsedStatesMap[initalStateXMLNode->value()]);
}

bool FiniteStateMachineIOManager::IsCompatibleWith(Editor *editor)
{
    return dynamic_cast<FiniteStateMachineEditor*> (editor) != nullptr ;
}

QString FiniteStateMachineIOManager::GetType()
{
    return "FiniteStateMachine";
}
