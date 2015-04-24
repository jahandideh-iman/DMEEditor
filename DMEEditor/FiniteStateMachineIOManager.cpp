#include "FiniteStateMachineIOManager.h"
#include <QFile>
#include "StateNode.h"
#include "StateLink.h"
#include "FiniteStateMachineEditor.h"
#include <QQueue>



FiniteStateMachineIOManager::FiniteStateMachineIOManager(FiniteStateMachineEditor *editor)
{
    this->editor = editor;
}

FiniteStateMachineIOManager::~FiniteStateMachineIOManager()
{

}

void FiniteStateMachineIOManager::SaveTo(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write("<DMEComponent type=\"FiniteStateMachine\" >\n" );
        SaveStates(&file);
        SaveTransitions(&file);
        SaveRoot(&file);
        file.write("</DMEComponent>\n");
        file.close();
    }
}


void FiniteStateMachineIOManager::SaveStates(QFile *file)
{
    file->write("   <States>\n");

    auto traversal = GetBreadthFirstTraversal();
    for(StateNode* state : traversal)
    {
        QString xPos = "XPos=\"" +QString::number(state->pos().x()) + "\"";
        QString yPos = "YPos=\"" +QString::number(state->pos().y()) + "\"";
        file->write(("       <State " + xPos +" "+ yPos + " >\n").toStdString().c_str());
        file->write(("           <Name>" + state->GetStateName()+"</Name>\n").toStdString().c_str());
        file->write(("           <UpdateAction>" + state->GetUpdateActionName()+"</UpdateAction>\n").toStdString().c_str());
        file->write(("           <EntryAction>" + state->GetEntryActionName()+"</EntryAction>\n").toStdString().c_str());
        file->write(("           <ExitAction>" + state->GetExitActionName()+"</ExitAction>\n").toStdString().c_str());
        file->write("       </State>\n");
    }

    file->write("   </States>\n");

}

void FiniteStateMachineIOManager::SaveTransitions(QFile *file)
{
    file->write("   <Transitions>\n");

    auto traversal = GetBreadthFirstTraversal();
    for(auto state : traversal)
    {
        for(auto l : state->GetOutLinks())
        {
            file->write("       <Transition>\n");
            file->write(("           <From>" + l->GetStartNode()->GetStateName()+"</From>\n").toStdString().c_str());
            file->write(("           <To>" + l->GetEndNode()->GetStateName()+"</To>\n").toStdString().c_str());
            file->write(("           <Condition>" + l->GetConditionName()+"</Condition>\n").toStdString().c_str());
            file->write("       </Transition>\n");
        }
    }
    file->write("    </Transitions>\n");
}

void FiniteStateMachineIOManager::SaveRoot(QFile *file)
{
    if(editor->GetRootNode() == nullptr)
        return;
    file->write(("  <InitialState>" + editor->GetRootNode()->GetStateName()+"</InitialState>\n").toStdString().c_str());
}

QVector<StateNode *> FiniteStateMachineIOManager::GetBreadthFirstTraversal()
{
    QVector<StateNode*> traversal;
    QQueue<StateNode*> queue;
    QVector<StateNode*> discovered;
    queue.enqueue(editor->GetRootNode());
    discovered.push_back(editor->GetRootNode());
    while(!queue.empty())
    {
        StateNode* state = queue.dequeue();
        traversal.push_back(state);

        for(auto l : state->GetOutLinks())
        {
            if( !discovered.contains(l->GetEndNode()))
            {
                queue.enqueue(l->GetEndNode());
                discovered.push_back(l->GetEndNode());
            }
        }

        for(auto l : state->GetInLinks())
        {
            if( !discovered.contains(l->GetEndNode()))
            {
                queue.enqueue(l->GetEndNode());
                discovered.push_back(l->GetEndNode());
            }
        }

    }

    return traversal;
}

void FiniteStateMachineIOManager::ReadFrom(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray dataArray = file.readAll();
        //QString data = file.readAll().toStdString();
        xml_document<> xmlData;
        xmlData.parse<0>(dataArray.data());
        xml_node<char>* rootXMLNode = xmlData.first_node("DMEComponent");
        if(rootXMLNode != nullptr )
        {
            ParseStates(rootXMLNode->first_node("States"));
            ParseTransitions(rootXMLNode->first_node("Transitions"));
            ParseInitialState(rootXMLNode->first_node("InitialState"));
        }

    }
    file.close();
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
    editor->AddNode(node);
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

    StateLink* link = new StateLink(parsedStatesMap[fromStateNode], parsedStatesMap[toStateNode], condition);
    editor->AddLink(link);
}

void FiniteStateMachineIOManager::ParseInitialState(FiniteStateMachineIOManager::XMLNode *initalStateXMLNode)
{
    if(initalStateXMLNode == nullptr)
        return;
    editor->SetRootNode(parsedStatesMap[initalStateXMLNode->value()]);
}



