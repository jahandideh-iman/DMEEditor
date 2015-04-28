#include "FiniteStateMachineEditor.h"
#include "FiniteStateMachineGraphicsScene.h"
#include "StateNode.h"
#include "StateTransition.h"

FiniteStateMachineEditor::FiniteStateMachineEditor()
{
    scene = new FiniteStateMachineGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setSceneRect(0,0,1000,1000);
    view->setMouseTracking(true);
}

FiniteStateMachineEditor::~FiniteStateMachineEditor()
{
    auto statesCopy(states);
    for(auto state : statesCopy)
        DeleteState(state);
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

void FiniteStateMachineEditor::DeleteState(StateNode *state)
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

void FiniteStateMachineEditor::DeleteTransition(StateTransition *transition)
{
    scene->removeItem(transition);
    delete transition;
}
