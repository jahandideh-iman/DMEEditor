#include "FiniteStateMachineEditor.h"
#include "FiniteStateMachineGraphicsScene.h"
#include "StateNode.h"
#include "StateTransition.h"

FiniteStateMachineEditor::FiniteStateMachineEditor()
{
    scene = new FiniteStateMachineGraphicsScene(this);
    view->setScene(scene);
}

FiniteStateMachineEditor::~FiniteStateMachineEditor()
{
    auto statesCopy(states);
    for(auto state : statesCopy)
        RemoveState(state);
}

void FiniteStateMachineEditor::CreateState(QPointF pos)
{
    StateNode * node = new StateNode();
    node->setPos(pos);

    AddState(node);
}

void FiniteStateMachineEditor::AddState(StateNode *state)
{
    states.push_back(state);
    scene->addItem(state);

    if(rootState == nullptr)
        SetRootState(state);
}

void FiniteStateMachineEditor::RemoveState(StateNode *state)
{
    if(rootState == state)
        rootState = nullptr;

    states.removeAll(state);
    scene->removeItem(state);
    delete state;
}

void FiniteStateMachineEditor::ConnectStates(StateNode *startState, StateNode *endState)
{
    if( startState != endState)
        AddTransition(new StateTransition(startState,endState));
}

const QVector<StateNode *> &FiniteStateMachineEditor::GetStates() const
{
    return states;
}

StateNode *FiniteStateMachineEditor::GetRootState()
{
    return rootState;
}

void FiniteStateMachineEditor::SetRootState(StateNode *node)
{
    if(rootState != nullptr)
        rootState->SetRootFlag(false);

    node->SetRootFlag(true);
    rootState = node;
}

void FiniteStateMachineEditor::AddTransition(StateTransition *transition)
{
    scene->addItem(transition);
}

void FiniteStateMachineEditor::RemoveTransition(StateTransition *transition)
{
    delete transition;
}

void FiniteStateMachineEditor::OnStateSelected(StateNode *selected)
{
    if(lastSelectedNode != nullptr && lastSelectedNode != selected)
    {
        ConnectStates(lastSelectedNode, selected);
        SetConnectingState(false);
    }
    else
    {
        lastSelectedNode = selected;
        SetConnectingState(true);
    }
}

void FiniteStateMachineEditor::CancelMouseTacking()
{
    SetConnectingState(false);
}

bool FiniteStateMachineEditor::IsInConnectingState()
{
    return lastSelectedNode != nullptr;
}

void FiniteStateMachineEditor::SetConnectingState(bool state)
{
    if(state == false)
    {
        lastSelectedNode = nullptr;
        scene->StopMouseTracking();
    }
    else
        scene->StartMouseTracking(lastSelectedNode);
}
